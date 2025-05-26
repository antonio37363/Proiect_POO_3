#pragma once
#include "Utilizator.hpp"
#include "ApplicationManager.hpp"
#include "Utils.hpp"
#include <iostream>

class Student : public Utilizator {
public:
    Student(const std::string& nume_, int id_) : Utilizator(nume_, id_) {}

    void meniu() override {
        auto& smartCursuri = ApplicationManager::getInstance().getCursuri();
        std::vector<Curs*> cursuri;
        for (auto& ptr : smartCursuri)
            cursuri.push_back(ptr.get());

        while (true) {
            std::cout << "\n===== MENIU STUDENT =====\n";
            std::cout << "1. Vezi toate cursurile tale\n";
            std::cout << "2. Vezi cate credite ai promovat\n";
            std::cout << "3. Vezi doar cursurile promovate\n";
            std::cout << "4. Cauta cursuri dupa tip\n";
            std::cout << "5. Exporta cursurile tale in CSV\n";
            std::cout << "0. Iesire\n";

            int opt;
            std::cin >> opt;

            if (opt == 1) {
                for (const auto& curs : cursuri)
                    if (curs->getIdStudent() == std::to_string(id))
                        curs->afiseaza();
            }

            else if (opt == 2) {
                int total = 0;
                for (const auto& curs : cursuri)
                    if (curs->getIdStudent() == std::to_string(id) && curs->estePromovat())
                        total += curs->getCredite();
                std::cout << "Total credite promovate: " << total << "\n";
            }

            else if (opt == 3) {
                bool found = false;
                for (const auto& curs : cursuri)
                    if (curs->getIdStudent() == std::to_string(id) && curs->estePromovat()) {
                        curs->afiseaza();
                        found = true;
                    }
                if (!found)
                    std::cout << "Nu ai cursuri promovate.\n";
            }

            else if (opt == 4) {
                std::cout << "Tipuri disponibile: obligatoriu, optional, facultativ\n";
                std::cout << "Introdu tipul dorit: ";
                std::string tip;
                std::cin >> tip;

                bool gasit = false;
                for (const auto& curs : cursuri) {
                    if (curs->getIdStudent() != std::to_string(id))
                        continue;

                    std::string type = typeid(*curs).name();
                    if ((tip == "obligatoriu" && type.find("Obligatoriu") != std::string::npos) ||
                        (tip == "optional" && type.find("Optional") != std::string::npos) ||
                        (tip == "facultativ" && type.find("Facultativ") != std::string::npos)) {
                        curs->afiseaza();
                        gasit = true;
                    }
                }

                if (!gasit)
                    std::cout << "Nu s-au gasit cursuri de acest tip pentru tine.\n";
            }
            else if (opt == 5) {
                const auto& cursuriSmart = ApplicationManager::getInstance().getCursuri();
                exportaCursuriStudent(cursuriSmart, std::to_string(id));
            }

            else if (opt == 0) {
                break;
            }

            else {
                std::cout << "Optiune invalida!\n";
            }
        }
    }
};
