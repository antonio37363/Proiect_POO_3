#pragma once
#include "Utilizator.hpp"
#include "ApplicationManager.hpp"
#include "CursFactory.hpp"
#include "Utils.hpp"
#include <iostream>

class Secretar : public Utilizator {
public:
    Secretar(const std::string& nume_, int id_) : Utilizator(nume_, id_) {}
 void meniu() override {
    while (true) {
        std::cout << "\n===== MENIU SECRETAR (" << nume << ") =====\n";
        std::cout << "1. Adauga curs\n";
        std::cout << "2. Afiseaza toate cursurile\n";
        std::cout << "3. Salveaza in fisier CSV\n";
        std::cout << "4. Afiseaza numarul total de cursuri\n";
        std::cout << "5. Sterge un curs dupa nume\n";
        std::cout << "6. Salveaza in fisier JSON\n"; 
        std::cout << "7. Modifica Curs\n";
        std::cout << "8. Sorteaza cursurile\n";
        std::cout << "9. Cauta curs avansat\n";
        std::cout << "0. Iesire\n";
        std::cout << "Alege optiunea: ";

        int opt;
        std::cin >> opt;

        auto& smartCursuri = ApplicationManager::getInstance().getCursuriModificabil();

        if (opt == 1) {
            // Lucram direct cu vectorul smart pointeri pentru adaugare
            ApplicationManager::getInstance().adaugaCurs(smartCursuri);
        } else {
            // Pentru restul opțiunilor, construim vectorul raw pointeri
            std::vector<Curs*> cursuri;
            for (auto& ptr : smartCursuri)
                cursuri.push_back(ptr.get());

            if (opt == 2) {
                ApplicationManager::getInstance().afiseazaCursuri(cursuri);
            }
            else if (opt == 3) {
                ApplicationManager::getInstance().salvareCSV(cursuri);
            }
            else if (opt == 4) {
                std::cout << "Numar total de cursuri create: " << Curs::getNrCursuri() << "\n";
            }
            else if (opt == 5) {
                ApplicationManager::getInstance().stergeCurs(smartCursuri);
                ApplicationManager::getInstance().salvareCSV(ApplicationManager::getInstance().getCursuriRaw());
                ApplicationManager::getInstance().salvareJSON(ApplicationManager::getInstance().getCursuriRaw());
            }

            else if (opt == 6) {
                ApplicationManager::getInstance().salvareJSON(cursuri);
            }
            else if (opt == 7) {
                ApplicationManager::getInstance().modificaCurs(cursuri);
            }
            else if (opt == 8) {
                ApplicationManager::getInstance().sorteazaCursuri(cursuri);
                
                
                // Refacem ordinea vectorului smart pointeri conform sortarii
                // smartCursuri este o referință directă, deci trebuie modificat.
                std::vector<std::shared_ptr<Curs>> cursuriNoi;
                for (auto ptrRaw : cursuri) {
                    for (auto& sp : smartCursuri) {
                        if (sp.get() == ptrRaw) {
                            cursuriNoi.push_back(sp);
                            break;
                        }
                    }
                }
                smartCursuri = std::move(cursuriNoi);
            }
            else if (opt == 9) {
                ApplicationManager::getInstance().cautaCursAvansat(cursuri);
            }
            else if (opt == 0) {
                break;
            }
            else {
                std::cout << "Optiune invalida.\n";
            }
        }
    }
}

};
