
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

    //n�v be�ll�t�sa
    //nevbe: �j n�v
    void setnev(const std::string nevbe);

    //�rt�k be�ll�t�sa
    //erbe: �j �rt�k
    void setert(const int erbe);

    //n�v lek�r�se
    //return n�v
    std::string getnev() const;

    //�rt�k lek�r�se
    //return �rt�k
    int getert() const;

    //k�d be�t�se
    //return igaz, ha a k�d j�
    bool beut(const int kod);

    //�jraind�tja a k�dolvas�t, �gy nem lesz aktiv�lva
    void aktival();

    //dtor
    virtual ~Kodolvaso();
};

#endif // KODOLVASO_H_INCLUDED
