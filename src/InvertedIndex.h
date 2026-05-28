#pragma once
#include "IDocument.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

class InvertedIndex {
private:
    // Stoc?m: Cuvânt -> Lista de c?i c?tre documentele în care apare
    std::map<std::string, std::vector<std::string>> indexData;

public:
    InvertedIndex() = default;

    // Adaug? un document în index
    void addDocument(const IDocument& doc);

    // Caut? un cuvânt ?i returneaz? c?ile documentelor
    std::vector<std::string> search(const std::string& word) const;
};