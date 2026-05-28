#pragma once
#include "IDocument.h"
#include <string>

class TextDocument : public IDocument {
    //Încapsularea
private:
    std::string filePath; // Aceasta este "caleFisier" din cerință
    std::string content;  // Acesta este "conținut" din cerință

public:
    // Constructor
    TextDocument(const std::string& path);

    // Suprascrierea metodelor din interfata
    std::string getPath() const override;
    std::string getContent() const override;
    void loadContent() override;
};