
#include <iostream>

#ifndef KODOLVASO_H_INCLUDED
#define KODOLVASO_H_INCLUDED

class Kodolvaso {
    std::string nev;
    int ertek;
    bool jokod;
public:
    //ctor
    //nevbe: az olvaso neve
    //erbe: az olvaso erteke
    Kodolvaso(const std::string &nevbe, const int erbe = 0);

    //név beállítása
    //nevbe: új név
    void setnev(const std::string nevbe);

    //érték beállítása
    //erbe: új érték
    void setert(const int erbe);

    //név lekérése
    //return név
    std::string getnev() const;

    //érték lekérése
    //return érték
    int getert() const;

    //kód beütése
    //return igaz, ha a kód jó
    bool beut(const int kod);

    //újraindítja a kódolvasót, így nem lesz aktiválva
    void aktival();

    //dtor
    virtual ~Kodolvaso();
};

#endif // KODOLVASO_H_INCLUDED
