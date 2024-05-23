#ifndef KODOLVASO_H_INCLUDED
#define KODOLVASO_H_INCLUDED

#include <iostream>

#include "String.h"
#include "memtrace.h"

class Kodolvaso {
    String nev;
    int ertek;
    bool jokod;
public:
    //ctor
    //nevbe: az olvaso neve
    //erbe: az olvaso erteke
    Kodolvaso(const String &nevbe, const int erbe = 0);

    //név beállítása
    //nevbe: új név
    void setnev(const String &nevbe);

    //érték beállítása
    //erbe: új érték
    void setert(const int erbe);

    //név lekérése
    //return név
    String getnev() const;

    //érték lekérése
    //return érték
    int getert() const;

    //kód beütése
    //return igaz, ha a kód jó
    bool beut(const int kod);

    //újraindítja a kódolvasót, így nem lesz aktiválva
    void aktival();

    //Visszaadja, hogy beütöttek-e jó kódot
    bool igaze();

    //Klónoz
    Kodolvaso* clone() const;

    //dtor
    virtual ~Kodolvaso();
};

#endif // KODOLVASO_H_INCLUDED
