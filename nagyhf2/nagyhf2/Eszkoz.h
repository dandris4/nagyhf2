#ifndef ESZKOZ_H_INCLUDED
#define ESZKOZ_H_INCLUDED

#include <iostream>

#include "String.h"
#include "memtrace.h"


enum eszkoztip {
    Erzek, Logik
};

std::istream& operator>>(std::istream& is, eszkoztip& rhs_l);

class Eszkoz {
    String nev;
    eszkoztip esztip;
public:
    //ctor
    Eszkoz(const String &be, const eszkoztip tipbe);

    //mctor
    Eszkoz(const Eszkoz& regi);

    //név beállítása
    virtual void setnev(const String &nevbe);

    //típus lekérdezése
    virtual eszkoztip gettip() const;

    //név lekérdezése
    virtual String getnev() const;

    //Visszaadja, hogy igaz-e az eszköz
    virtual bool igaze(int ido) = 0;

    //klónozás, a kollekcióhoz, illetve a szirénánál meg hasonlóknál ne legyen probléma, ha olyat törlünk, ami nem hozzá tartozik
    virtual Eszkoz* clone() const = 0;

    //dtor
    virtual ~Eszkoz();
};

#endif // ESZKOZ_H_INCLUDED
