#pragma once
#include <string>

// [POO - Abstractizare] Clasa pur abstracta (Interfata).
// O folosim pentru a defini un "contract" pe care orice tip de document trebuie sa il respecte.
class IDocument {
public:

    // Destructor virtual obligatoriu pentru o stergere corecta a memoriei in polimorfism
    virtual ~IDocument() = default;

    // Metode pur virtuale (= 0). Nu au cod aici, vor fi scrise in clasele derivate.
    virtual std::string getPath() const = 0;
    virtual std::string getContent() const = 0;
    virtual void loadContent() = 0; // Metoda care va citi din fisier
};

// Arhitectura cu Interfața IDocument să fie solidă de la început
// Utilizarea unei interfețe (IDocument) permite motorului de căutare să fie extensibil
// Interfața