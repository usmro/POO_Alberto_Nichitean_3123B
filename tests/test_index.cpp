#include <iostream>
#include <cassert> // Biblioteca standard pentru teste simple
#include <fstream>
#include "../src/InvertedIndex.h"
#include "../src/TextDocument.h"

// Functie utilitara pentru a nu crea fisiere de mana inainte de testare
void createTestFile(const std::string& name, const std::string& content) {
    std::ofstream file(name);
    if (file.is_open()) {
        file << content;
        file.close();
    }
}

void runTests() {
    std::cout << "--- Rulare Teste Unitare ---\n";

    // 1. Setup: Pregatim datele pentru test
    std::string testFileName = "test_doc.txt";
    createTestFile(testFileName, "Acesta este un test simplu si eficient.");

    TextDocument doc(testFileName);
    doc.loadContent();

    InvertedIndex index;
    index.addDocument(doc);

    // 2. [Test Unitare] Testam comportamentul aplicatiei
    // Test 1: Cautare cuvant valid. assert() va opri programul cu eroare daca e fals.
    auto res1 = index.search("test");
    assert(res1.size() == 1 && res1[0] == testFileName);
    std::cout << "[PASSED] Test 1: Cuvant valid gasit corect.\n";

    // Test 2: Verificare filtrare stop-words (cuvantul "si" este in setul de ignorare)
    auto res2 = index.search("si");
    assert(res2.empty());
    std::cout << "[PASSED] Test 2: Stop-word a fost ignorat corect.\n";

    // Test 3: Cautare cuvant care nu a fost in text
    auto res3 = index.search("masina");
    assert(res3.empty());
    std::cout << "[PASSED] Test 3: Cuvant inexistent tratat corect.\n";

    std::cout << "Toate testele au trecut cu succes!\n";
}

int main() {
    runTests();
    return 0;
}