#include "TextDocument.h"
#include "IndexException.h"
#include <fstream>
#include <sstream>


// Constructor care initializeaza calea (folosim lista de initializare pentru eficienta)
TextDocument::TextDocument(const std::string& path) : filePath(path) {}


// [POO - Incapsulare] Returnam valoarea variabilelor private printr-un "getter"
std::string TextDocument::getPath() const {
    return filePath;
}

std::string TextDocument::getContent() const {
    return content;
}


// [POO - Suprascriere] Implementarea metodei de incarcare
void TextDocument::loadContent() {
    std::ifstream file(filePath);

    // Validare: Verificam daca fisierul exista si poate fi deschis
    if (!file.is_open()) {


        // [POO - Exceptii] Aruncam eroarea noastra customizata in loc sa blocam programul
        throw IndexException("Eroare critica: Nu am putut deschide fisierul " + filePath);
    }

    // Citim tot continutul fisierului eficient, folosind un buffer
    std::stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();
    file.close();  // Eliberam resursa (fisierul)
}