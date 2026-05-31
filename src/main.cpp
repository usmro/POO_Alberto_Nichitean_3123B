#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem> // [NOU - Întâlnirea 3] Biblioteca standard C++17 pentru lucrul cu directoare
#include "TextDocument.h"
#include "InvertedIndex.h"
#include "IndexException.h" // Includem excepția noastră custom

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
    std::cout << "=== Motor de Cautare Documente (Faza 3) ===\n\n";

    std::string testFolder = "documente_test";

    // 1. Generăm automat câteva documente text pentru testare in noul folder
    createDummyFileInFolder(testFolder, "istoric.txt", "Stefan cel Mare a fost domnitor in Moldova si a castigat multe lupte.");
    createDummyFileInFolder(testFolder, "stiinta.txt", "In fizica, teoria relativitatii a fost formulata de Albert Einstein.");
    createDummyFileInFolder(testFolder, "programare.txt", "Un programator bun scrie cod curat si foloseste un index pentru cautare.");

    InvertedIndex index;

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
    std::string command;
    while (true) {
        std::cout << "Introdu un cuvant pt cautare (sau 'exit' pt a inchide): ";
        std::cin >> command;

        if (command == "exit") {
            break;
        }

        std::vector<std::string> results = index.search(command);

        if (results.empty()) {
            std::cout << " -> Cuvantul '" << command << "' nu a fost gasit (sau este stop-word).\n";
        }
        else {
            std::cout << " -> Cuvantul '" << command << "' apare in:\n";
            for (const std::string& path : results) {
                std::cout << "    - " << path << "\n";
            }
        }
        std::cout << "------------------------------------------------\n";
    }

    // 4. Eliberarea corectă a memoriei pentru a preveni memory leaks
    for (IDocument* doc : documents) {
        delete doc;
    }

    std::cout << "\nProgram incheiat curat. La revedere!\n";
    return 0;
}