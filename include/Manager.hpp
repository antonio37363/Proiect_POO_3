#pragma once
#include <vector>
#include <memory>
#include <iostream>

template <typename T>
class Manager {
private:
    std::vector<T> obiecte;

public:
    void adauga(const T& obiect) {
        obiecte.push_back(obiect);
    }

    void afiseazaToate() const {
        for (const auto& obj : obiecte) {
            obj->afiseaza();
        }
    }

    const std::vector<T>& getToate() const {
        return obiecte;
    }

    std::vector<T>& getToateModificabil() {
    return obiecte;
    }

};
