#pragma once
#include <string>

// Clasa pur abstracta (Interfata)
class IDocument {
public:
    virtual ~IDocument() = default;
    virtual std::string getPath() const = 0;
    virtual std::string getContent() const = 0;
    virtual void loadContent() = 0; // Metoda care va citi din fisier
};

// Arhitectura cu Interfața IDocument să fie solidă de la început
// Utilizarea unei interfețe (IDocument) permite motorului de căutare să fie extensibil
// Interfața