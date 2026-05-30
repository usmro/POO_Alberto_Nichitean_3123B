#pragma once
#include "IDocument.h"
#include <string>
#include <vector>
#include <map>
#include <set>

class InvertedIndex {
private:

    // [POO - Sabloane STL] Folosim std::map pentru a lega un cuvant de o lista de documente
    std::map<std::string, std::vector<std::string>> indexData;

    // [Cerinta Facultativa] O lista de cuvinte ignorate pentru a optimiza cautarea
    std::set<std::string> stopWords = { "si", "in", "la", "pe", "de", "un", "o", "cu", "din", "sau" };

    // [POO - Incapsulare] Metoda privata, folosita doar intern pentru a verifica lista de stop-words
    bool isStopWord(const std::string& word) const;

public:
    InvertedIndex() = default;


    // Aici injectam orice obiect care respecta interfata IDocument
    void addDocument(const IDocument& doc);

    // Returneaza lista de fisiere in care a fost gasit cuvantul
    std::vector<std::string> search(const std::string& word) const;
};