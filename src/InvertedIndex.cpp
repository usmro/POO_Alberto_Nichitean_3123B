#include "InvertedIndex.h"
#include <sstream>
#include <algorithm>
#include <cctype>


// Metoda privata care verifica daca un cuvant face parte din lista de stop-words
bool InvertedIndex::isStopWord(const std::string& word) const {

    // std::set::find cauta rapid cuvantul. Daca nu ajunge la final (end), inseamna ca l-a gasit.
    return stopWords.find(word) != stopWords.end();
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
// Functia de cautare
std::vector<std::string> InvertedIndex::search(const std::string& word) const {
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