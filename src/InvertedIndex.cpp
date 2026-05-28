#include "InvertedIndex.h"
#include <sstream>
#include <algorithm>

void InvertedIndex::addDocument(const IDocument& doc) {
    std::string text = doc.getContent();
    std::string path = doc.getPath();
    
    // Transformăm textul în litere mici pentru o căutare uniformă
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    
    std::stringstream ss(text);
    std::string word;
    
    // Spargem textul în cuvinte și le adăugăm în Map
    while (ss >> word) {
        // Dacă documentul nu este deja în lista pentru acest cuvânt, îl adăugăm
        auto& docList = indexData[word];
        if (std::find(docList.begin(), docList.end(), path) == docList.end()) {
            docList.push_back(path);
        }
    }
}

std::vector<std::string> InvertedIndex::search(const std::string& word) const {
    std::string searchWord = word;
    std::transform(searchWord.begin(), searchWord.end(), searchWord.begin(), ::tolower);
    
    auto it = indexData.find(searchWord);
    if (it != indexData.end()) {
        return it->second; // Returnăm lista de documente
    }
    
    return {}; // Dacă nu am găsit cuvântul, returnăm o listă goală
}