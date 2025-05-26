#pragma once
#include <memory>
#include "Manager.hpp"
#include "Curs.hpp"

class ApplicationManager {
private:
    Manager<std::shared_ptr<Curs>> managerCursuri;

    // Constructor privat -> nimeni nu poate face obiect cu `new`
    ApplicationManager() = default;

public:
    // Ștergem copierea – nu vrem să existe 2 instanțe
    ApplicationManager(const ApplicationManager&) = delete;
    ApplicationManager& operator=(const ApplicationManager&) = delete;

    // Funcție statică care oferă referința unică la instanță
    static ApplicationManager& getInstance() {
        static ApplicationManager instanta;
        return instanta;
    }

    // Funcții publice de lucru
    void adaugaCurs(const std::shared_ptr<Curs>& curs) {
        managerCursuri.adauga(curs);
    }

    void afiseazaCursuri() const {
        managerCursuri.afiseazaToate();
    }

    const std::vector<std::shared_ptr<Curs>>& getCursuri() const {
        return managerCursuri.getToate();
    }

    std::vector<std::shared_ptr<Curs>>& getCursuriModificabil() {
    return managerCursuri.getToateModificabil();
    }

    void adaugaCurs(std::vector<std::shared_ptr<Curs>>& cursuri);
    void afiseazaCursuri(const std::vector<Curs*>& cursuri);
    void salvareCSV(const std::vector<Curs*>& cursuri);
    void salvareJSON(const std::vector<Curs*>& cursuri);
    void stergeCurs(std::vector<std::shared_ptr<Curs>>& cursuri);
    void modificaCurs(std::vector<Curs*>& cursuri);
    void sorteazaCursuri(std::vector<Curs*>& cursuri);
    void cautaCursAvansat(const std::vector<Curs*>& cursuri) const;


    void exportaCursuriStudent(const std::vector<Curs*>& cursuri, const std::string& idStudent) const;



    std::vector<Curs*> getCursuriRawModificabil() {
    static std::vector<Curs*> cursuriRaw;
    cursuriRaw.clear();

    for (auto& sp : managerCursuri.getToateModificabil()) {
        cursuriRaw.push_back(sp.get());
    }

    return cursuriRaw;
    }

    std::vector<Curs*> getCursuriRaw() const {
        std::vector<Curs*> cursuriRaw;
        for (const auto& sp : managerCursuri.getToate()) {
            cursuriRaw.push_back(sp.get());
        }
        return cursuriRaw;
    }


};
