# POO_Alberto_Nichitean
Acest repository conține activitatea desfășurată la disciplina POO.


# Proiect POO - Motor de Căutare (Întâlnirea 1)

**Student:** [Nichitean Alberto]

Acesta este stadiul inițial al proiectului meu pentru laboratorul de POO. Am pus la punct structura de bază și m-am asigurat că totul rulează corect pe Linux (WSL).

## 📂 Ce am adăugat până acum:

### În folderul `src/` (Cod Sursă):

* **`IDocument.h`**: Am creat această interfață pentru a defini ce înseamnă un document în sistemul meu (Abstractizare).

* **`TextDocument.h` & `.cpp`**: Am implementat clasa cerută pentru documente text. Aceasta moștenește `IDocument` și gestionează calea fișierului și conținutul acestuia.

* **`InvertedIndex.h` & `.cpp`**: Am adăugat "creierul" motorului de căutare, care folosește un `std::map` pentru a lega cuvintele de documente.

* **`main.cpp`**: Un punct de pornire unde testez dacă obiectele mele se creează corect și dacă moștenirea funcționează.

### În folderul `docs/` (Documentație):

* **`documentatie.md`**: Am explicat pe scurt analiza temei și conceptele de POO folosite.

* **`diagrama_uml.png`**: Am inclus o schiță vizuală a claselor mele pentru a arăta relația de moștenire.