#include <iostream>
#include <fstream>
#include <vector>
#include "TextDocument.h"
#include "InvertedIndex.h"
#include "IndexException.h" // Includem excepția noastră custom

// Funcție ajutătoare pentru a crea rapid fișiere de test
void createDummyFile(const std::string& name, const std::string& content) {
    std::ofstream file(name);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}

int main() {
    std::cout << "=== Motor de Cautare Documente (Faza 2) ===\n\n";

    // 1. Generăm automat câteva documente text pentru testare
    createDummyFile("istoric.txt", "Stefan cel Mare a fost domnitor in Moldova si a castigat multe lupte.");
    createDummyFile("stiinta.txt", "In fizica, teoria relativitatii a fost formulata de Albert Einstein.");
    createDummyFile("programare.txt", "Un programator bun scrie cod curat si foloseste un index pentru cautare.");

    InvertedIndex index;

    // [POO - Polimorfism] Cream un vector de pointeri catre clasa de BAZA (IDocument)
    std::vector<IDocument*> documents;

    // [POO - Exceptii] Bloc try-catch pentru prinderea posibilelor erori (ex: lipsa fisier)
    // 2. Bloc try-catch pentru prinderea Excepțiilor (Cerință Întâlnirea 2)
    try {
        std::cout << "[INFO] Se pregatesc documentele...\n";

        // Demonstrăm Polimorfismul (alocăm TextDocument ca IDocument)
        // [POO - Polimorfism] Alocam obiecte derivate (TextDocument) in pointeri de baza (IDocument)
        documents.push_back(new TextDocument("istoric.txt"));
        documents.push_back(new TextDocument("stiinta.txt"));
        documents.push_back(new TextDocument("programare.txt"));

        // DACA VREAU SĂ TESTEZ EXCEPȚIA, DECOMENTEX LINIA DE MAI JOS:
        // documents.push_back(new TextDocument("fisier_lipsa.txt"));

        // Încărcăm și indexăm fiecare document
        for (IDocument* doc : documents) {
            doc->loadContent(); // Aici se poate arunca IndexException
            index.addDocument(*doc);
        }
        std::cout << "[INFO] Indexare completata cu succes!\n\n";

    }
    catch (const IndexException& e) {
        // Dacă un fișier lipsește, prindem eroarea curat, fără să crape programul
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