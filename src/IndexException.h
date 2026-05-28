#pragma once
#include <exception>
#include <string>



// [POO - Exceptii Custom & Mostenire] Cream propria noastra eroare mostenind clasa de baza std::exception
class IndexException : public std::exception {
private:
    std::string message;
public:
    // Constructor
    IndexException(const std::string& msg) : message(msg) {}

    // Suprascriem metoda what() pentru a returna mesajul nostru atunci cand programul "crapa"
    const char* what() const noexcept override {
        return message.c_str();
    }
};