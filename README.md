# Proiect POO - Management Cursuri Universitare

Acesta este un proiect simplu în C++ pentru gestionarea cursurilor universitare, cu roluri de secretar și student.

## Funcționalități

- Adaugă, modifică, șterge și afișează cursuri (obligatorii, opționale, facultative)
- Exportă cursuri în formate CSV și JSON
- Autentificare simplă pentru secretar și student
- Meniu interactiv în consolă

## Cum se compilează


g++ -Iinclude src/main.cpp src/ApplicationManager.cpp src/Curs.cpp src/CursObligatoriu.cpp src/CursOptional.cpp src/CursFacultativ.cpp src/Exceptii.cpp src/Serializable.cpp src/Utils.cpp -o main.exe

## Cum se rulează

    ./main.exe