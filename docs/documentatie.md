# Proiect POO: Motor de Căutare Documente (Tema 3123B)

## 1. Analiza Temei

Tema presupune realizarea unui sistem capabil să indexeze documente text și să permită căutarea eficientă a cuvintelor. Am ales o abordare modulară care să permită extinderea ulterioară a tipurilor de documente suportate (ex: PDF sau HTML). Pentru a optimiza căutarea, sistemul include un filtru anti-plagiat/stop-words.

## 2. Clasele și Interfețele Aplicației

* **IDocument (Interfață):** Clasa pur abstractă care definește comportamentul obligatoriu pentru orice document (încărcare conținut, obținere cale).

* **TextDocument:** Implementarea concretă pentru fișiere de tip text, care moștenește interfața `IDocument`.

* **InvertedIndex:** „Creierul” aplicației, care mapează fiecare cuvânt către lista de documente în care acesta apare. Gestionează direct ignorarea cuvintelor de legătură (stop-words).

* **IndexException:** O clasă proprie de erori, creată pentru a raporta probleme la nivelul fișierelor (ex: fișier corupt sau inexistent).

## 3. Concepte POO Utilizate

* **Abstractizare:** Realizată prin utilizarea clasei abstracte `IDocument` pentru a defini un model general de document, forțând un "contract" de bază.

* **Moștenire:** - `TextDocument` derivă din `IDocument`, preluând și implementând metodele obligatorii.

  - `IndexException` derivă din clasa de bază `std::exception`, integrându-se perfect în sistemul standard C++.

* **Încapsulare:** Atributele (`filePath`, `indexData`, `stopWords`) sunt declarate `private` pentru a proteja integritatea datelor. Am folosit metode private, precum `isStopWord()`, pentru a ascunde logica internă față de restul programului.

* **Polimorfism Dinamic:** Utilizat prin metode virtuale. Clasa `InvertedIndex` și logica din aplicația principală procesează pointeri de tip `IDocument*`, permițând tratarea uniformă a diferitelor tipuri de fișiere la runtime.

* **Tratarea Excepțiilor:** Aplicată prin folosirea blocurilor `try-catch` pentru a intercepta obiecte de tip `IndexException` fără ca programul să se oprească necontrolat.

## 4. Testare și Validare

* **Teste Unitare:** Logica motorului de căutare este validată independent folosind `assert()`, demonstrând gestionarea corectă a cuvintelor valide, a stop-words-urilor și a termenilor inexistenți.

![Diagrama UML](diagrama_uml.png)