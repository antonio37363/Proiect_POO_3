#pragma once
#include <memory>
#include "CursObligatoriu.hpp"
#include "CursFacultativ.hpp"
#include "CursOptional.hpp"

class CursFactory {
public:
    static std::shared_ptr<CursObligatoriu> creeazaObligatoriu(
        const std::string& nume,
        const std::string& profesor,
        int credite,
        int scris,
        int colocviu,
        int proiect,
        int activitate
    ) {
        
        auto curs = std::make_shared<CursObligatoriu>(
        "Nume", "Profesor", 5, 7, 8, 9, 10
        );

        curs->setNume(nume);
        curs->setProfesor(profesor);
        curs->setCredite(credite);
        curs->setNote(scris, colocviu, proiect, activitate);
        return curs;
    }

    static std::shared_ptr<CursFacultativ> creeazaFacultativ(
        const std::string& nume,
        const std::string& profesor,
        int credite,
        int eseu,
        int proiect,
        int prezenta
    ) {
        auto curs = std::make_shared<CursFacultativ>(
                 "Nume", "Profesor", 3, 9, 8, 100
        );

        curs->setNume(nume);
        curs->setProfesor(profesor);
        curs->setCredite(credite);
        curs->setNote(eseu, proiect, prezenta);
        return curs;
    }


    static std::shared_ptr<CursOptional> creeazaOptional(
        const std::string& nume,
        const std::string& profesor,
        int credite,
        int proiect1,
        int proiect2,
        int proiect3
    ) {
        auto curs = std::make_shared<CursOptional>(
             "Nume", "Profesor", 4, 8, 9, 10
        );

        curs->setNume(nume);
        curs->setProfesor(profesor);
        curs->setCredite(credite);
        curs->setNote(proiect1, proiect2, proiect3);
        return curs;
    }
};


