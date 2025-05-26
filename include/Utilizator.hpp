#pragma once
#include <string>

class Utilizator {
protected:
    std::string nume;
    int id;

public:
    Utilizator(const std::string& nume_, int id_) : nume(nume_), id(id_) {}
    virtual ~Utilizator() = default;

    virtual void meniu() = 0;  // fiecare copil va avea propriul meniu

    std::string getNume() const { return nume; }
    int getId() const { return id; }
};
