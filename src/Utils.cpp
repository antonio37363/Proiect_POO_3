#include "Curs.hpp"
#include "Utils.hpp"
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <iostream>

std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}


void exportaCursuriStudent(const std::vector<std::shared_ptr<Curs>>& cursuri, const std::string& idStudent) {
    std::string filename = "cursuri_" + idStudent + ".csv";
    std::ofstream fout(filename);

    if (!fout.is_open()) {
        std::cerr << "Nu pot deschide fisierul pentru scriere!\n";
        return;
    }

    for (const auto& curs : cursuri) {
        if (curs->getIdStudent() == idStudent) {
            Serializable* serial = dynamic_cast<Serializable*>(curs.get());
            if (serial)
                fout << serial->toCSV() << "\n";
        }
    }


    fout.close();
    std::cout << "Cursurile tale au fost exportate in: " << filename << "\n";
}




bool esteIDSecretarValid(const std::string& id) {
    std::ifstream fin("secretari_ids.txt");
    std::string linie;

    while (std::getline(fin, linie)) {
        if (linie == id)
            return true;
    }

    return false;
}


bool esteIDStudentValid(const std::string& id) {
    std::ifstream fin("studenti.txt");
    if (!fin.is_open()) {
        std::cerr << "Eroare: Nu am putut deschide fisierul studenti.txt\n";
        return false;
    }

    std::unordered_set<std::string> validIDs;
    std::string line;
    while (std::getline(fin, line)) {
        validIDs.insert(line);
    }
    fin.close();

    return validIDs.find(id) != validIDs.end();
}