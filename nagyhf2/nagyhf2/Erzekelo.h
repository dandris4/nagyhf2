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

    //�j �rt�k be�ll�t�sa
    //ujert: az �j �rt�k
    void setert(const int ujert);

    //�j t�pus be�ll�t�sa
    //ujerz: az �j t�pus
    void seterztip(const ErzTipus ujerz);

    //T�pus lek�rdez�se
    //return: tipus
    ErzTipus geterztip() const;

    //�rt�k lek�rdez�se
    //return: ertek
    int getert() const;

    //Visszaadja, hogy jelez-e az �rz�kel�
    bool igaze(int ido = 0);

    //kl�noz�s, a kollekci�hoz, illetve a szir�n�n�l meg hasonl�kn�l ne legyen probl�ma, ha olyat t�rl�nk, ami nem hozz� tartozik
    Erzekelo* clone() const;


};

#endif // ERZEKELO_H_INCLUDED
