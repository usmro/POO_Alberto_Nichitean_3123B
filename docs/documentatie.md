# Proiect POO: Motor de Căutare Documente (Tema 3123B)

## 1. Analiza Temei
Tema presupune realizarea unui sistem capabil să indexeze documente text și să permită căutarea eficientă a cuvintelor. Am ales o abordare modulară care să permită extinderea ulterioară a tipurilor de documente suportate (ex: PDF sau HTML). Pentru a optimiza căutarea, sistemul include un filtru anti-plagiat/stop-words, iar interacțiunea utilizatorului este jurnalizată printr-un sistem decuplat de log-uri.

## 2. Clasele și Interfețele Aplicației
* **IDocument (Interfață):** Clasa pur abstractă care definește comportamentul obligatoriu pentru orice document (încărcare conținut, obținere cale).
* **TextDocument:** Implementarea concretă pentru fișiere de tip text, care moștenește interfața `IDocument`.
* **InvertedIndex:** „Creierul” aplicației. Stochează un `std::map` ce mapează fiecare cuvânt către lista de documente asociate. Gestionează ignorarea cuvintelor de legătură (stop-words) și rezolvă interogările logice.
* **IndexException:** O clasă proprie de erori, creată pentru a raporta probleme la nivelul fișierelor sau directoarelor (ex: folder inexistent).
* **IObserver & Logger:** Interfața abstractă și clasa concretă utilizate pentru implementarea tiparului Observer, având rolul de a monitoriza automat sistemul.

## 3. Concepte POO Utilizate
* **Abstractizare:** Realizată prin utilizarea claselor abstracte (`IDocument`, `IObserver`) pentru a defini "contracte" clare de implementare.
* **Moștenire:** - `TextDocument` derivă din `IDocument`.
  - `IndexException` derivă din clasa de bază `std::exception`.
  - `Logger` derivă din `IObserver`.
* **Încapsulare:** Atributele (`filePath`, `indexData`, `stopWords`, `observers`) sunt declarate `private` pentru a proteja integritatea datelor. Metodele ajutătoare precum `isStopWord()` sau `searchSingleWord()` sunt ascunse față de exterior.
* **Polimorfism Dinamic:** Utilizat prin metode virtuale. Clasa `InvertedIndex` procesează pointeri de tip `IDocument*` și `IObserver*`, permițând tratarea uniformă a obiectelor derivate la runtime.
* **Tratarea Excepțiilor:** Aplicată prin folosirea blocurilor `try-catch` pentru a intercepta obiecte de tip `IndexException` curat, prevenind oprirea necontrolată a programului.
* **Design Pattern (Observer):** Implementat pentru a decupla total logica de căutare de logica de jurnalizare. Motorul de căutare nu știe nimic despre `Logger`; el doar își notifică lista globală de observatori, sporind extensibilitatea aplicației.

## 4. Funcționalități Tehnice Avansate
* **Citire Dinamică:** Sistemul utilizează biblioteca standard `std::filesystem` (C++17) pentru a scana automat directorul țintă și a încărca fișierele valide în memorie.
* **Căutare Rapidă și Case-Insensitive:** Căutările folosesc arborele binar din spatele `std::map`, oferind un timp de acces logaritmic - $O(\log n)$. Termenii sunt normalizați complet (ex: `Fizica` și `fizica` sunt tratați identic).
* **Procesare Booleană (AND / OR):** Algoritmul de căutare rezolvă intersecții (pentru clauza `AND` - returnând doar documentele cu toate cuvintele cerute) și reuniuni (pentru clauza `OR`).

## 5. Testare și Validare
* **Teste Unitare:** Logica motorului de căutare este validată independent folosind macroul `assert()`, demonstrând gestionarea corectă a cuvintelor valide, a operațiilor booleene, a stop-words-urilor și a termenilor inexistenți.

![Diagrama UML](diagrama_uml.png)