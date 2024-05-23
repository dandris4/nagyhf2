#ifndef TIPUS_H_INCLUDED
#define TIPUS_H_INCLUDED

#include <iostream>

#include "memtrace.h"
#include "String.h"

struct ErzTipus {
    String nev;
    int alapert, also, felso;
public:
    //ctor
    ErzTipus(const String &sbe, const int alpbe, const int felsbe, const int alsbe);

    //név beállítása
    //nevbe: új név
    void setnev(const String &nevbe);

    //alap érték beállítása
    //erbe: új érték
    void setalap(const int erbe);

    //alsó határérték beállítása
    //erbe: új érték
    void setalso(const int erbe);

    //felsõ határérték beállítása
    //erbe: új érték
    void setfelso(const int erbe);

    //név lekérése
    //return név
    String getnev() const;

    //alap érték lekérése
    //return érték
    int getalap() const;

    //alsó határérték lekérése
    //return érték
    int getalso() const;

    //felsõ határérték lekérése
    //return érték
    int getfelso() const;
};


#endif // TIPUS_H_INCLUDED
