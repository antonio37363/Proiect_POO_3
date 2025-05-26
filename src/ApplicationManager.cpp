#include "ApplicationManager.hpp"
#include "Curs.hpp"
#include "CursObligatoriu.hpp"
#include "CursOptional.hpp"
#include "CursFacultativ.hpp"
#include "Serializable.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>


void ApplicationManager::adaugaCurs(std::vector<std::shared_ptr<Curs>>& cursuri)
{
    int tip;
    std::cout << "Ce tip de curs doresti sa adaugi?\n";
    std::cout << "1. Curs Obligatoriu\n";
    std::cout << "2. Curs Optional\n";
    std::cout << "3. Curs Facultativ\n";
    std::cout << "Alege tipul: ";
    std::cin >> tip;

    std::string nume, profesor;
    int credite;
    std::cout << "Introdu numele cursului: ";
    std::cin.ignore();
    std::getline(std::cin, nume);
    std::cout << "Introdu numele profesorului: ";
    std::getline(std::cin, profesor);
    std::cout << "Introdu numarul de credite: ";
    std::cin >> credite;

    std::string idStudent;
    std::cout << "Introdu ID-ul studentului: ";
    std::cin >> idStudent;

    try
    {
        if (tip == 1)
        {
            int scris, colocviu, proiect, activitate;
            std::cout << "Nota examen scris: ";
            std::cin >> scris;
            std::cout << "Nota colocviu: ";
            std::cin >> colocviu;
            std::cout << "Nota proiect: ";
            std::cin >> proiect;
            std::cout << "Nota activitate laborator: ";
            std::cin >> activitate;

            auto curs = std::make_shared<CursObligatoriu>(nume, profesor, credite, scris, colocviu, proiect, activitate);
            curs->setIdStudent(idStudent);
            cursuri.push_back(curs);
        }
        else if (tip == 2)
        {
            int p1, p2, p3;
            std::cout << "Nota proiect 1: ";
            std::cin >> p1;
            std::cout << "Nota proiect 2: ";
            std::cin >> p2;
            std::cout << "Nota proiect 3: ";
            std::cin >> p3;

            auto curs = std::make_shared<CursOptional>(nume, profesor, credite, p1, p2, p3);
            curs->setIdStudent(idStudent);
            cursuri.push_back(curs);
        }
        else if (tip == 3)
        {
            int eseu, proiect, prezenta;
            std::cout << "Nota eseu: ";
            std::cin >> eseu;
            std::cout << "Nota proiect: ";
            std::cin >> proiect;
            std::cout << "Procent prezenta: ";
            std::cin >> prezenta;

            auto curs = std::make_shared<CursFacultativ>(nume, profesor, credite, eseu, proiect, prezenta);
            curs->setIdStudent(idStudent);
            cursuri.push_back(curs);
        }
        else
        {
            std::cout << "Tip invalid.\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Eroare: " << e.what() << '\n';
    }
}


void ApplicationManager::afiseazaCursuri(const std::vector<Curs*>& cursuri)
{
    if (cursuri.empty())
    {
        std::cout << "Nu exista cursuri adaugate.\n";
        return;
    }

    for (const auto& curs : cursuri)
    {
        curs->afiseaza();
        std::cout << "-------------------------\n"; // separator intre cursuri
    }
}



void ApplicationManager::salvareCSV(const std::vector<Curs*>& vector_cursuri)
{
    std::ofstream fout("cursuri.csv");

    if (!fout.is_open())
    {
        std::cout << "Eroare: Nu am putut deschide fisierul cursuri.csv\n";
        return;
    }

    for (auto& curs : vector_cursuri)
    {
        Serializable* serial = dynamic_cast<Serializable*>(curs);
        if (serial)
        {
            fout << serial->toCSV() << '\n';
        }
    }

    fout.close();
    std::cout << "Salvare in cursuri.csv finalizata cu succes!\n";
}


void ApplicationManager::salvareJSON(const std::vector<Curs*>& cursuri)
{
    std::ofstream fout("cursuri.json");

    if (!fout.is_open())
    {
        std::cout << "Eroare: Nu am putut deschide fisierul cursuri.json\n";
        return;
    }

    fout << "[\n";
    for (size_t i = 0; i < cursuri.size(); ++i)
    {
        Serializable* serial = dynamic_cast<Serializable*>(cursuri[i]);
        if (serial)
        {
            fout << serial->toJSON();
            if (i != cursuri.size() - 1)
                fout << ",\n"; // punem virgula intre obiecte
        }
    }
    fout << "\n]\n";

    fout.close();
    std::cout << "Salvare in cursuri.json finalizata cu succes!\n";
}


void ApplicationManager::stergeCurs(std::vector<std::shared_ptr<Curs>>& cursuri) {
    std::string numeCautat;
    std::cout << "Introdu numele cursului de sters: ";
    std::cin.ignore();  // să curețe bufferul
    std::getline(std::cin, numeCautat);

    bool gasit = false;
    for (auto it = cursuri.begin(); it != cursuri.end(); ++it) {
        if ((*it)->getNume() == numeCautat) {
            cursuri.erase(it);
            gasit = true;
            std::cout << "Cursul a fost sters cu succes!\n";
            break;
        }
    }

    if (!gasit) {
        std::cout << "Cursul nu a fost gasit.\n";
    }
}




void ApplicationManager::modificaCurs(std::vector<Curs*>& cursuri)
{
    std::string numeCautat;
    std::cout << "Introdu numele cursului pe care vrei sa il modifici: ";
    std::getline(std::cin >> std::ws, numeCautat);

    bool gasit = false;
    for (auto& curs : cursuri)
    {
        if (curs->getNume() == numeCautat)
        {
            gasit = true;
            // Verificam ce tip de curs este
            if (auto* oblig = dynamic_cast<CursObligatoriu*>(curs))
            {
                std::cout << "Ce vrei sa modifici?\n";
                std::cout << "1. Nota scris\n";
                std::cout << "2. Nota colocviu\n";
                std::cout << "3. Nota proiect\n";
                std::cout << "4. Nota activitate\n";
                int alegere;
                std::cin >> alegere;
                int nouaNota;
                std::cout << "Introdu noua nota: ";
                std::cin >> nouaNota;

                if (alegere == 1) oblig->setNotaScris(nouaNota);
                else if (alegere == 2) oblig->setNotaColocviu(nouaNota);
                else if (alegere == 3) oblig->setNotaProiect(nouaNota);
                else if (alegere == 4) oblig->setNotaActivitate(nouaNota);
                else std::cout << "Optiune invalida!\n";

                curs->setDataModificare(getCurrentDate());
            }
            else if (auto* opt = dynamic_cast<CursOptional*>(curs))
            {
                std::cout << "Ce vrei sa modifici?\n";
                std::cout << "1. Nota proiect 1\n";
                std::cout << "2. Nota proiect 2\n";
                std::cout << "3. Nota proiect 3\n";
                int alegere;
                std::cin >> alegere;
                int nouaNota;
                std::cout << "Introdu noua nota: ";
                std::cin >> nouaNota;

                if (alegere == 1) opt->setProiect1(nouaNota);
                else if (alegere == 2) opt->setProiect2(nouaNota);
                else if (alegere == 3) opt->setProiect3(nouaNota);
                else std::cout << "Optiune invalida!\n";

                curs->setDataModificare(getCurrentDate());
            }
            else if (auto* facult = dynamic_cast<CursFacultativ*>(curs))
            {
                std::cout << "Ce vrei sa modifici?\n";
                std::cout << "1. Nota eseu\n";
                std::cout << "2. Nota proiect\n";
                std::cout << "3. Prezenta\n";
                int alegere;
                std::cin >> alegere;
                
                if (alegere == 1)
                {
                    int nouaNota;
                    std::cout << "Introdu noua nota la eseu: ";
                    std::cin >> nouaNota;
                    facult->setNotaEseu(nouaNota);
                }
                else if (alegere == 2)
                {
                    int nouaNota;
                    std::cout << "Introdu noua nota la proiect: ";
                    std::cin >> nouaNota;
                    facult->setNotaProiect(nouaNota);
                }
                else if (alegere == 3)
                {
                    int nouProcent;
                    std::cout << "Introdu noul procent de prezenta: ";
                    std::cin >> nouProcent;
                    facult->setPrezenta(nouProcent);
                }
                else
                {
                    std::cout << "Optiune invalida!\n";
                }

                curs->setDataModificare(getCurrentDate());
            }
            else
            {
                std::cout << "Tip de curs necunoscut!\n";
            }

            break; // am gasit si modificat, iesim
        }
    }

    if (!gasit)
    {
        std::cout << "Cursul nu a fost gasit.\n";
    }
}



void ApplicationManager::sorteazaCursuri(std::vector<Curs*>& cursuri)
{
    if (cursuri.empty())
    {
        std::cout << "Nu exista cursuri de sortat.\n";
        return;
    }

    std::cout << "Cum doresti sa sortezi cursurile?\n";
    std::cout << "1. Dupa nume (A-Z)\n";
    std::cout << "2. Dupa nota finala (descrescator)\n";
    std::cout << "3. Dupa numarul de credite (descrescator)\n";
    std::cout << "Alege optiunea: ";

    int alegere;
    std::cin >> alegere;

    if (alegere == 1)
    {
        std::sort(cursuri.begin(), cursuri.end(), [](Curs* a, Curs* b)
        {
            return a->getNume() < b->getNume();
        });
        std::cout << "Sortare dupa nume realizata cu succes!\n";
    }
    else if (alegere == 2)
    {
        std::sort(cursuri.begin(), cursuri.end(), [](Curs* a, Curs* b)
        {
            return a->nota_finala() > b->nota_finala();
        });
        std::cout << "Sortare dupa nota finala realizata cu succes!\n";
    }
    else if (alegere == 3)
    {
        std::sort(cursuri.begin(), cursuri.end(), [](Curs* a, Curs* b)
        {
            return a->getCredite() > b->getCredite();
        });
        std::cout << "Sortare dupa numar credite realizata cu succes!\n";
    }
    else
    {
        std::cout << "Optiune invalida!\n";
    }
}


void ApplicationManager::cautaCursAvansat(const std::vector<Curs*>& cursuri) const
{
    if (cursuri.empty())
    {
        std::cout << "Nu exista cursuri inregistrate.\n";
        return;
    }

    std::cout << "Criterii de cautare:\n";
    std::cout << "1. Cauta dupa nume curs\n";
    std::cout << "2. Cauta dupa profesor\n";
    std::cout << "3. Cauta cursuri cu nota finala peste o valoare\n";
    std::cout << "Alege optiunea: ";

    int alegere;
    std::cin >> alegere;
    std::cin.ignore(); // curata bufferul ca sa mearga getline()

    if (alegere == 1)
    {
        std::string nume;
        std::cout << "Introdu numele cursului: ";
        std::getline(std::cin, nume);

        bool gasit = false;
        for (const auto& curs : cursuri)
        {
            if (curs->getNume() == nume)
            {
                curs->afiseaza();
                gasit = true;
            }
        }
        if (!gasit)
            std::cout << "Nu s-a gasit niciun curs cu acest nume.\n";
    }
    else if (alegere == 2)
    {
        std::string numeProfesor;
        std::cout << "Introdu numele profesorului: ";
        std::getline(std::cin, numeProfesor);

        bool gasit = false;
        for (const auto& curs : cursuri)
        {

            if (curs->getProfesor() == numeProfesor)
            {
                curs->afiseaza();
                gasit = true;
            }
        }
        if (!gasit)
            std::cout << "Nu s-a gasit niciun curs predat de acest profesor.\n";
    }
    else if (alegere == 3)
    {
        double prag;
        std::cout << "Introdu pragul minim al notei finale: ";
        std::cin >> prag;

        bool gasit = false;
        for (const auto& curs : cursuri)
        {
            if (curs->nota_finala() >= prag)
            {
                curs->afiseaza();
                gasit = true;
            }
        }
        if (!gasit)
            std::cout << "Nu s-au gasit cursuri cu nota peste pragul dat.\n";
    }
    else
    {
        std::cout << "Optiune invalida!\n";
    }
}




void ApplicationManager::exportaCursuriStudent(const std::vector<Curs*>& cursuri, const std::string& idStudent) const {
    std::ofstream fout("cursuri_student_" + idStudent + ".csv");

    if (!fout.is_open()) {
        std::cout << "Eroare la deschiderea fisierului pentru export.\n";
        return;
    }

    for (const auto& curs : cursuri) {
        Serializable* serial = dynamic_cast<Serializable*>(curs);
        if (serial) {
            fout << serial->toCSV() << '\n';
        }
    }

    fout.close();
    std::cout << "Export complet in fisierul cursuri_student_" << idStudent << ".csv\n";
}
