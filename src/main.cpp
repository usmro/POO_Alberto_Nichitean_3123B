#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem> // [NOU - Întâlnirea 3] Biblioteca standard C++17 pentru lucrul cu directoare
#include "TextDocument.h"
#include "InvertedIndex.h"
#include "IndexException.h" // Includem excepția noastră custom
#include "Logger.h"         // [NOU - Observer] Includem clasa Logger pentru inregistrarea cautarilor

namespace fs = std::filesystem; // Folosim un alias pentru a scrie mai usor

// Funcție ajutătoare pentru a crea rapid fișiere de test direct intr-un folder specificat
void createDummyFileInFolder(const std::string& folder, const std::string& name, const std::string& content) {
    fs::create_directory(folder); // [NOU] Ne asiguram ca folderul exista inainte sa scriem
    std::ofstream file(folder + "/" + name);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}

int main() {
    std::cout << "=== Motor de Cautare Documente (Faza 3 FINAL) ===\n\n";

    std::string testFolder = "documente_test";

    // 1. Generăm automat câteva documente text pentru testare in noul folder
    createDummyFileInFolder(testFolder, "istoric.txt", "Stefan cel Mare a fost domnitor in Moldova si a castigat multe lupte.");
    createDummyFileInFolder(testFolder, "stiinta.txt", "In fizica, teoria relativitatii a fost formulata de Albert Einstein.");
    createDummyFileInFolder(testFolder, "programare.txt", "Un programator bun scrie cod curat si foloseste un index pentru cautare in logica.");

    InvertedIndex index;

    // [POO - Observer (Bonus)] Cream obiectul Logger si il adaugam in lista de observatori a motorului de cautare
    Logger searchLogger;
    index.addObserver(&searchLogger);

    // [POO - Polimorfism] Cream un vector de pointeri catre clasa de BAZA (IDocument)
    std::vector<IDocument*> documents;

    // [POO - Exceptii] Bloc try-catch pentru prinderea posibilelor erori (ex: lipsa fisier)
    // 2. Bloc try-catch pentru prinderea Excepțiilor (Cerință Întâlnirea 2)
    try {
        std::cout << "[INFO] Se pregatesc documentele din folderul '" << testFolder << "'...\n";

        // [CERINTĂ OBLIGATORIE ÎNTÂLNIREA 3] Încărcare dinamică din director
        // Verificăm dacă folderul există și dacă este într-adevăr un director
        if (fs::exists(testFolder) && fs::is_directory(testFolder)) {

            // Iterăm automat prin absolut toate fișierele pe care le găsește în folder
            for (const auto& entry : fs::directory_iterator(testFolder)) {
                if (entry.is_regular_file()) { // Ne asigurăm că e fișier, nu un alt sub-folder
                    std::string filePath = entry.path().string(); // Extragem calea fișierului

                    // [POO - Polimorfism] Alocam obiecte derivate (TextDocument) in pointeri de baza (IDocument)
                    documents.push_back(new TextDocument(filePath));
                    std::cout << "  -> Gasit si pregatit: " << filePath << "\n";
                }
            }
        }
        else {
            // Dacă din diverse motive nu poate citi folderul, aruncăm excepția noastră custom
            throw IndexException("Folderul specificat pentru documente nu exista sau nu poate fi accesat!");
        }

        // DACA VREAU SĂ TESTEZ EXCEPȚIA PENTRU FIȘIER LIPSĂ, DECOMENTEZ LINIA DE MAI JOS:
        // documents.push_back(new TextDocument("fisier_care_nu_exista.txt"));

        // Încărcăm și indexăm fiecare document gasit
        std::cout << "\n[INFO] Se incepe indexarea...\n";
        for (IDocument* doc : documents) {
            doc->loadContent(); // Aici se poate arunca IndexException
            index.addDocument(*doc);
        }
        std::cout << "[INFO] Indexare completata cu succes!\n\n";

    }
    catch (const IndexException& e) {
        // Dacă un fișier/folder lipsește, prindem eroarea curat, fără să crape programul
        std::cerr << "[EROARE PRINSĂ CONFORM POO]: " << e.what() << "\n\n";

        // Curățăm memoria alocată până la eroare
        for (IDocument* doc : documents) delete doc;
        return 1; // Ieșim cu cod de eroare
    }

    // 3. Interfața Interactivă (Meniul cu buclă while)
    int optiune;
    while (true) {
        std::cout << "\n================================================\n";
        std::cout << "             MENIU MOTOR DE CAUTARE             \n";
        std::cout << "================================================\n";
        std::cout << " 1. Efectueaza o cautare (Simpla sau AND/OR)\n";
        std::cout << " 2. Afiseaza documentele indexate in sistem\n";
        std::cout << " 0. Iesire program\n";
        std::cout << "------------------------------------------------\n";
        std::cout << "Alege o optiune: ";

        // Verificam daca utilizatorul introduce ceva valid (numar)
        if (!(std::cin >> optiune)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Eroare: Te rog sa introduci un numar valid!\n";
            continue;
        }

        if (optiune == 0) {
            break;
        }
        else if (optiune == 1) {
            std::string command;
            // [Actualizat Intalnirea 3] Informam utilizatorul ca acum poate cauta cu AND / OR
            std::cout << "\n-> Introdu un cuvant (ex: 'teoria') sau o cautare avansata (ex: 'teoria AND fizica'):\nCauta: ";

            // Folosim getline cu std::ws in loc de std::cin simplu, pentru ca cin se opreste la primul spatiu 
            // iar noi trebuie sa citim toata linia "cuvant1 AND cuvant2"
            std::getline(std::cin >> std::ws, command);

            // Apelam metoda noastra modernizata care suporta operatori logici
            std::vector<std::string> results = index.search(command);

            std::cout << "\n[ REZULTATE ]\n";
            if (results.empty()) {
                std::cout << " -> Interogarea '" << command << "' nu a returnat niciun rezultat valid.\n";
            }
            else {
                for (const std::string& path : results) {
                    std::cout << "    - Document: " << path << "\n";
                }
            }
        }
        else if (optiune == 2) {
            std::cout << "\n[ DOCUMENTE INCARCATE ]\n";
            if (documents.empty()) {
                std::cout << " -> Niciun document nu este incarcat momentan.\n";
            }
            else {
                for (IDocument* doc : documents) {
                    // [POO - Polimorfism] Apelam metoda virtuala getPath() prin pointerul de baza
                    std::cout << "    - " << doc->getPath() << "\n";
                }
            }
        }
        else {
            std::cout << "\n[!] Optiune invalida! Te rog sa alegi 0, 1 sau 2.\n";
        }
    }

    // 4. Eliberarea corectă a memoriei pentru a preveni memory leaks
    for (IDocument* doc : documents) {
        delete doc;
    }

    std::cout << "\nProgram incheiat curat. La revedere!\n";
    return 0;
}