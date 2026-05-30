#pragma once
#include "IDocument.h"
#include <string>


// [POO - Mostenire] TextDocument mosteneste (implementeaza) interfata IDocument
class TextDocument : public IDocument {
    //Încapsularea
private:


    // [POO - Incapsulare] Datele sunt private. Nu pot fi modificate din afara clasei.
    std::string filePath; // Aceasta este "caleFisier" din cerință
    std::string content;  // Acesta este "conținut" din cerință

public:
    // Constructor care seteaza calea fisierului
    TextDocument(const std::string& path);

    // [POO - Suprascriere/Polimorfism] Implementam metodele cerute de interfata IDocument
    std::string getPath() const override;
    std::string getContent() const override;
    void loadContent() override;
};