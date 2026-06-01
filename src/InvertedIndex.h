#pragma once
#include "IDocument.h"
#include "IObserver.h" // [NOU - Intalnirea 3] Includem interfata Observer pentru a putea raporta cautarile
#include <string>
#include <vector>
#include <map>
#include <set>

class InvertedIndex {
private:

    // [POO - Sabloane STL] Folosim std::map pentru a lega un cuvant de o lista de documente
    std::map<std::string, std::vector<std::string>> indexData;

    // [Cerinta Facultativa] O lista de cuvinte ignorate pentru a optimiza cautarea
    std::set<std::string> stopWords = { "si", "in", "la", "pe", "de", "un", "o", "cu", "din", "sau" };

    // [POO - Design Pattern: Observer] Lista in care pastram toti "observatorii" (cum ar fi Logger-ul)
    std::vector<IObserver*> observers;

    // [POO - Incapsulare] Metoda privata, folosita doar intern pentru a verifica lista de stop-words
    bool isStopWord(const std::string& word) const;

    // [POO - Incapsulare & Observer] Metoda privata folosita pentru a notifica automat toti observatorii cand utilizatorul cauta ceva
    void notifyObservers(const std::string& query) const;

    // [Cerinta Bonus] Metoda privata creata pentru a gestiona cautarea de baza (un singur cuvant), in timp ce functia principala de search se ocupa de AND/OR
    std::vector<std::string> searchSingleWord(const std::string& word) const;

public:
    InvertedIndex() = default;

    // [POO - Design Pattern: Observer] Metoda prin care "atasam" un obiect observator (Logger-ul) la acest motor de cautare
    void addObserver(IObserver* obs);

    // Aici injectam orice obiect care respecta interfata IDocument
    void addDocument(const IDocument& doc);

    // [Actualizat pt Cerinta Bonus] Returneaza lista de fisiere in care a fost gasit cuvantul. 
    // Acum suporta si query-uri complexe (ex: "fizica AND teoria" sau "cod OR domnitor")
    std::vector<std::string> search(const std::string& query) const;
};