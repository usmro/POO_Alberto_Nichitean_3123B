#include <iostream>
#include "TextDocument.h"
#include "InvertedIndex.h"

int main() {
    std::cout << "--- Motor de Cautare Documente Text ---" << std::endl;

    InvertedIndex index;

    // Testăm polimorfismul
    // Polimorfismul
    // Folosesc polimorfism în metoda de indexare ca să fac Motorul de Căutare extensibil
    IDocument* doc1 = new TextDocument("fisier1.txt");
    IDocument* doc2 = new TextDocument("fisier2.txt");

    std::cout << "Clasele de baza si mostenirea (IDocument -> TextDocument) au fost configurate cu succes!" << std::endl;
    std::cout << "Pentru început codul este pregătit" << std::endl;

    delete doc1;
    delete doc2;

    return 0;
}