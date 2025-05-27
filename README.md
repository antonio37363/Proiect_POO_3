# Proiect POO - Management Cursuri Universitare

Acesta este un proiect simplu în C++ pentru gestionarea cursurilor universitare, cu roluri de secretar și student.

## Funcționalități

* Adaugă, modifică, șterge și afișează cursuri (obligatorii, opționale, facultative)
* Exportă cursuri în formate CSV și JSON
* Autentificare simplă pentru secretar și student
* Meniu interactiv în consolă

## Cum se compilează

g++ -Iinclude src/main.cpp src/ApplicationManager.cpp src/Curs.cpp src/CursObligatoriu.cpp src/CursOptional.cpp src/CursFacultativ.cpp src/Exceptii.cpp src/Serializable.cpp src/Utils.cpp -o main.exe

## Cum se rulează

```
./main.exe
```

---

## Reflecție asupra cerințelor implementate

În cadrul acestei teme am urmat cerințele legate de OOP avansat, folosind principii SOLID, design patterns și programare generică.

### ✔️ 1. Clase și funcții template

Am implementat o clasă generică `Manager<T>`, care gestionează un vector de obiecte de tip `T`. Clasa este folosită în `ApplicationManager` pentru a administra cursurile (prin `Manager<std::shared_ptr<Curs>>`). Acest pattern mi-a permis să generalizez gestionarea obiectelor într-un mod reutilizabil și curat (`Manager.hpp`).

În plus, am folosit o funcție template `afisareVector<T>()` în `Utils.hpp`, care afișează elementele dintr-un vector generic folosind `afiseaza()`. Aceasta demonstrează utilizarea programării generice în combinație cu polimorfismul.

### ✔️ 2. Design Patterns

#### ✅ Singleton

`ApplicationManager` este implementat ca un singleton clasic, folosind un constructor privat și o metodă statică `getInstance()` care returnează instanța unică. Astfel, gestionez centralizat toate operațiile din aplicație (`ApplicationManager.hpp`).

#### ✅ Factory

Am implementat un pattern Factory în `CursFactory.hpp`, pentru a crea instanțe de `CursObligatoriu`, `CursOptional` și `CursFacultativ`. Acest lucru ajută la abstractizarea logicii de creare a cursurilor și separă clar inițializarea de folosirea lor.

### ✔️ 3. Principiile SOLID

* **S - Single Responsibility**: Fiecare clasă are o responsabilitate clară – `Curs` definește interfața, `ApplicationManager` gestionează aplicația, `Utils` oferă funcții de utilitate, iar `CursFactory` se ocupă de instanțiere.
* **O - Open/Closed**: Am adăugat tipuri noi de cursuri (facultative, opționale etc.) fără a modifica logica existentă din clasele de bază, ci prin moștenire.
* **L - Liskov Substitution**: Am folosit pointeri la `Curs*` sau `shared_ptr<Curs>` în toate părțile aplicației, și toate clasele derivate (`CursObligatoriu`, `CursOptional`, `CursFacultativ`) pot fi substituite fără probleme.
* **I - Interface Segregation**: Am separat comportamentele legate de serializare într-o interfață dedicată `Serializable`.
* **D - Dependency Inversion**: `ApplicationManager` și `Secretar` lucrează cu interfețe (precum `Serializable`) și tipuri abstracte (`Curs*`), nu cu implementări concrete.

### ✔️ 4. Alte funcționalități relevante

Am adăugat și funcționalități extra (meniu pentru secretar/student, export CSV/JSON, sortare, căutare avansată), care au fost tratate modular, fără a încărca clasele existente. Acestea contribuie la extensibilitate și testabilitate.
