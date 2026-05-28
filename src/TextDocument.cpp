#include "TextDocument.h"
#include <fstream>
#include <sstream>
#include <iostream>

//Clasa concretă

TextDocument::TextDocument(const std::string& path) : filePath(path) {}

std::string TextDocument::getPath() const {
    return filePath;
}

std::string TextDocument::getContent() const {
    return content;
}

void TextDocument::loadContent() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Eroare: Nu am putut deschide fisierul " << filePath << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();
    file.close();
}