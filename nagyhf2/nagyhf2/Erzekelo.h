#ifndef ERZEKELO_H_INCLUDED
#define ERZEKELO_H_INCLUDED

#include "Eszkoz.h"
#include "Tipus.h"

#include <iostream>

#include "memtrace.h"

class Erzekelo :public Eszkoz {
    int ertek;
    ErzTipus tipus;
public:
    //ctor
    Erzekelo(const String &nev, const ErzTipus tipbe);

    //ctor
    Erzekelo(const String &nev = "");

    //mctor
    Erzekelo(Erzekelo& be);

    //Új érték beállítása
    //ujert: az új érték
    void setert(const int ujert);

    //Új típus beállítása
    //ujerz: az új típus
    void seterztip(const ErzTipus ujerz);

    //Típus lekérdezése
    //return: tipus
    ErzTipus geterztip() const;

    //Érték lekérdezése
    //return: ertek
    int getert() const;

    //Visszaadja, hogy jelez-e az érzékelõ
    bool igaze(int ido = 0);

    //klónozás, a kollekcióhoz, illetve a szirénánál meg hasonlóknál ne legyen probléma, ha olyat törlünk, ami nem hozzá tartozik
    Erzekelo* clone() const;


};

#endif // ERZEKELO_H_INCLUDED
