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

    //n�v be�ll�t�sa
    virtual void setnev(const String &nevbe);

    //t�pus lek�rdez�se
    virtual eszkoztip gettip() const;

    //n�v lek�rdez�se
    virtual String getnev() const;

    //Visszaadja, hogy igaz-e az eszk�z
    virtual bool igaze(int ido) = 0;

    //kl�noz�s, a kollekci�hoz, illetve a szir�n�n�l meg hasonl�kn�l ne legyen probl�ma, ha olyat t�rl�nk, ami nem hozz� tartozik
    virtual Eszkoz* clone() const = 0;

    //dtor
    virtual ~Eszkoz();
};

#endif // ESZKOZ_H_INCLUDED
