#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "Curs.hpp"
#include "Serializable.hpp"
#include <iostream>

std::string getCurrentDate();

template <typename T>
void afisareVector(const std::vector<T>& v) {
    for (const auto& elem : v) {
        elem->afiseaza();
    }
}

void exportaCursuriStudent(const std::vector<std::shared_ptr<Curs>>& cursuri, const std::string& idStudent);



void adaugaCurs(std::vector<Curs*>& cursuri);
void afiseazaCursuri(const std::vector<Curs*>& cursuri);
void salvareCSV(const std::vector<Curs*>& cursuri);
void salvareJSON(const std::vector<Curs*>& cursuri);
void stergeCurs(std::vector<Curs*>& cursuri);
void modificaCurs(std::vector<Curs*>& cursuri);
void sorteazaCursuri(std::vector<Curs*>& cursuri);
void cautaCursAvansat(const std::vector<Curs*>& cursuri);
void exportaCursuriStudent(const std::vector<std::shared_ptr<Curs>>& cursuri, const std::string& idStudent);



bool esteIDSecretarValid(const std::string& id);

bool esteIDStudentValid(const std::string& id);
