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

    //n�v be�ll�t�sa
    //nevbe: �j n�v
    void setnev(const String &nevbe);

    //�rt�k be�ll�t�sa
    //erbe: �j �rt�k
    void setert(const int erbe);

    //n�v lek�r�se
    //return n�v
    String getnev() const;

    //�rt�k lek�r�se
    //return �rt�k
    int getert() const;

    //k�d be�t�se
    //return igaz, ha a k�d j�
    bool beut(const int kod);

    //�jraind�tja a k�dolvas�t, �gy nem lesz aktiv�lva
    void aktival();

    //Visszaadja, hogy be�t�ttek-e j� k�dot
    bool igaze();

    //Kl�noz
    Kodolvaso* clone() const;

    //dtor
    virtual ~Kodolvaso();
};

#endif // KODOLVASO_H_INCLUDED
