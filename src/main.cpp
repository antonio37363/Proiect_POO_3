#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Curs.hpp"
#include "CursObligatoriu.hpp"
#include "CursOptional.hpp"
#include "CursFacultativ.hpp"
#include "Serializable.hpp"
#include "Exceptii.hpp"
#include "Manager.hpp"
#include "ApplicationManager.hpp"
#include "Student.hpp"
#include "Secretar.hpp"
#include "Utils.hpp"



void afiseazaCrediteTotale(const std::vector<Curs*>& cursuri)
{
    int total = 0;

    for (const auto& curs : cursuri)
        total += curs->getCredite();

    std::cout << "Numar total de credite: " << total << "\n";
}



void incarcareCSV(std::vector<std::shared_ptr<Curs>>& cursuri) {
    std::ifstream fin("cursuri.csv");
    if (!fin.is_open()) {
        std::cout << "Eroare: Nu am putut deschide fisierul cursuri.csv\n";
        return;
    }

    std::string linie;
    while (std::getline(fin, linie)) {
        std::istringstream ss(linie);
        std::vector<std::string> campuri;
        std::string camp;
        while (std::getline(ss, camp, ',')) {
            campuri.push_back(camp);
        }

        try {
            if (campuri.empty()) continue;

            std::string tip = campuri[0];
            if (tip == "obligatoriu" && campuri.size() == 10) {
                auto curs = std::make_shared<CursObligatoriu>(
                    campuri[1], campuri[2], std::stoi(campuri[3]),
                    std::stoi(campuri[4]), std::stoi(campuri[5]),
                    std::stoi(campuri[6]), std::stoi(campuri[7])
                );
                curs->setDataModificare(campuri[8]);
                curs->setIdStudent(campuri[9]);
                cursuri.push_back(curs);
            } 
            else if (tip == "optional" && campuri.size() == 9) {
                auto curs = std::make_shared<CursOptional>(
                    campuri[1], campuri[2], std::stoi(campuri[3]),
                    std::stoi(campuri[4]), std::stoi(campuri[5]), std::stoi(campuri[6])
                );
                curs->setDataModificare(campuri[7]);
                curs->setIdStudent(campuri[8]);
                cursuri.push_back(curs);
            } 
            else if (tip == "facultativ" && campuri.size() == 9) {
                int procent_prezenta = std::stoi(campuri[6].substr(0, campuri[6].size() - 1));
                auto curs = std::make_shared<CursFacultativ>(
                    campuri[1], campuri[2], std::stoi(campuri[3]),
                    std::stoi(campuri[4]), std::stoi(campuri[5]), procent_prezenta
                );
                curs->setDataModificare(campuri[7]);
                curs->setIdStudent(campuri[8]);
                cursuri.push_back(curs);
            } 
            else {
                std::cout << "Linie invalida ignorata.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Eroare la incarcare: " << e.what() << "\n";
        }
    }
    fin.close();
    std::cout << "Incarcare din cursuri.csv finalizata cu succes!\n";
}




void vizualizareCursuriStudent(const std::vector<Curs*>& cursuri) {
    std::string id;
    std::cout << "Introdu ID-ul tau: ";
    std::cin >> id;

    bool gasit = false;
    for (const auto& curs : cursuri) {
        if (curs->getIdStudent() == id) {
            curs->afiseaza();
            std::cout << "------------------------\n";
            gasit = true;
        }
    }

    if (!gasit)
        std::cout << "Nu ai niciun curs inregistrat.\n";
}




void afiseazaCreditePromovate(const std::vector<Curs*>& cursuri) {
    int totalCredite = 0, creditePromovate = 0;

    for (const auto& curs : cursuri) {
        totalCredite += curs->getCredite();
        if (curs->nota_finala() >= 5)
            creditePromovate += curs->getCredite();
    }

    std::cout << "Ai promovat " << creditePromovate << " din " << totalCredite << " credite.\n";
}


int main() {
        auto& manager = ApplicationManager::getInstance();

    // Folosește referința non-const
    auto& cursuriSmart = manager.getCursuriModificabil(); // referință non-const la vectorul de shared_ptr

    incarcareCSV(cursuriSmart);  // încarcă direct în vectorul smart pointeri

    std::vector<Curs*> cursuri;
    for (auto& ptr : cursuriSmart) {
        cursuri.push_back(ptr.get());
    }

    std::unique_ptr<Utilizator> utilizator;

    std::cout << "Esti:\n1. Secretar\n2. Student\nAlege: ";
    int rol;
    std::cin >> rol;

    std::string nume;
    std::string idStr;
    std::cin.ignore();
    std::cout << "Introdu numele: ";
    std::getline(std::cin, nume);
    std::cout << "Introdu ID numeric: ";
    std::getline(std::cin, idStr);

    if (rol == 1) {
        if (!esteIDSecretarValid(idStr)) {
            std::cout << "ID invalid! Acces refuzat.\n";
            return 0;
        }
        utilizator = std::make_unique<Secretar>(nume, std::stoi(idStr));
    } else {
        if (!esteIDStudentValid(idStr)) {
            std::cout << "ID student invalid! Acces refuzat.\n";
            return 0;
        }
        utilizator = std::make_unique<Student>(nume, std::stoi(idStr));
    }

    utilizator->meniu();

    // Salvează cursurile la final (folosind vector raw ptr)
    ApplicationManager::getInstance().salvareCSV(cursuri);
    ApplicationManager::getInstance().salvareJSON(cursuri);

    return 0;
}
