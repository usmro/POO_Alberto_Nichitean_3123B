#include "InvertedIndex.h"
#include <sstream>
#include <algorithm>
#include <cctype>


// Metoda privata care verifica daca un cuvant face parte din lista de stop-words
bool InvertedIndex::isStopWord(const std::string& word) const {
    // std::set::find cauta rapid cuvantul. Daca nu ajunge la final (end), inseamna ca l-a gasit.
    return stopWords.find(word) != stopWords.end();
}

// [NOU - Observer] Adaugam un observator (de ex. Logger-ul) in lista interna
void InvertedIndex::addObserver(IObserver* obs) {
    observers.push_back(obs);
}

// [NOU - Observer] Parcurgem lista de observatori si ii "notificam" ce a cautat utilizatorul
void InvertedIndex::notifyObservers(const std::string& query) const {
    for (IObserver* obs : observers) {
        obs->update(query);
    }
}


// [POO - Polimorfism] Functia primeste o referinta la IDocument, dar va lucra cu TextDocument
void InvertedIndex::addDocument(const IDocument& doc) {
    std::string text = doc.getContent();
    std::string path = doc.getPath();

    // [STL] Transformam textul in litere mici pentru ca "Ana" si "ana" sa fie acelasi cuvant
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);

    // Curatam semnele de punctuatie (inlocuim virgula/punctul cu spatiu)
    for (char& c : text) {
        if (ispunct(c)) {
            c = ' ';
        }
    }

    std::stringstream ss(text);
    std::string word;


    // Spargem textul in cuvinte individuale si iteram prin ele
    while (ss >> word) {
        // [Cerinta facultativa] Filtram stop-words si cuvintele de o singura litera
        if (word.length() > 1 && !isStopWord(word)) {

            // Accesam lista de documente a acestui cuvant
            auto& docList = indexData[word];

            // Daca fisierul curent nu este deja in lista, il adaugam pentru a evita duplicatele
            if (std::find(docList.begin(), docList.end(), path) == docList.end()) {
                docList.push_back(path);
            }
        }
    }
}

// [Transformata din functia veche de cautare] Acum e o metoda ajutatoare pentru a cauta un singur cuvant
std::vector<std::string> InvertedIndex::searchSingleWord(const std::string& word) const {
    std::string searchWord = word;

    // Ne asiguram ca si cuvantul cautat de utilizator este transformat in litere mici
    std::transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);

    // Cautam in Map (O(log n) - cautare foarte rapida)
    auto it = indexData.find(searchWord);
    if (it != indexData.end()) {
        return it->second; // Returnam lista de fisiere gasita
    }

    // Daca nu s-a gasit cuvantul, returnam o lista goala
    return {};
}

// [NOU - Cerinta Facultativa] Noua functie principala de cautare, suporta operatori logici AND / OR
std::vector<std::string> InvertedIndex::search(const std::string& query) const {

    // 1. [Observer] Mai intai de toate, anuntam Logger-ul ca s-a inregistrat o cautare
    notifyObservers(query);

    // 2. Verificam daca utilizatorul incearca o cautare avansata
    size_t andPos = query.find(" AND ");
    size_t orPos = query.find(" OR ");

    // Cazul 1: Cautare cu AND (Intersectie - documentul trebuie sa aiba AMBELE cuvinte)
    if (andPos != std::string::npos) {
        // Extragem cuvintele din stanga si din dreapta lui " AND "
        std::string w1 = query.substr(0, andPos);
        std::string w2 = query.substr(andPos + 5); // 5 e lungimea lui " AND "

        auto res1 = searchSingleWord(w1);
        auto res2 = searchSingleWord(w2);

        std::vector<std::string> result;
        for (const auto& doc : res1) {
            // Daca documentul din prima lista se gaseste si in a doua lista, il pastram
            if (std::find(res2.begin(), res2.end(), doc) != res2.end()) {
                result.push_back(doc);
            }
        }
        return result;
    }
    // Cazul 2: Cautare cu OR (Reuniune - documentul trebuie sa aiba CEL PUTIN un cuvant)
    else if (orPos != std::string::npos) {
        // Extragem cuvintele din stanga si din dreapta lui " OR "
        std::string w1 = query.substr(0, orPos);
        std::string w2 = query.substr(orPos + 4); // 4 e lungimea lui " OR "

        auto res1 = searchSingleWord(w1);
        auto res2 = searchSingleWord(w2);

        std::vector<std::string> result = res1; // Punem direct toate documentele din primul cuvant
        for (const auto& doc : res2) {
            // Le adaugam pe cele din al doilea cuvant doar daca nu sunt deja in lista (evitam duplicatele)
            if (std::find(result.begin(), result.end(), doc) == result.end()) {
                result.push_back(doc);
            }
        }
        return result;
    }

    // Cazul 3: Daca utilizatorul a scris un singur cuvant, fara operatori, apelam cautarea simpla
    return searchSingleWord(query);
}