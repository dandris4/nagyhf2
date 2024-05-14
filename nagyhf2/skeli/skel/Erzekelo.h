#ifndef ERZEKELO_H_INCLUDED
#define ERZEKELO_H_INCLUDED

#include "Eszkoz.h"
#include "Tipus.h"

class Erzekelo :public Eszkoz {
    int ertek;
    ErzTipus tipus;
public:
    //ctor
    Erzekelo(const std::string nev, const ErzTipus tipbe);

    //�j �rt�k be�ll�t�sa
    //ujert: az �j �rt�k
    void setert(const int ujert);

    //�rt�k lek�rdez�se
    //return: ertek
    int getert() const;

    //Visszaadja, hogy jelez-e az �rz�kel�
    bool igaze();

    //kl�noz�s, a kollekci�hoz, illetve a szir�n�n�l meg hasonl�kn�l ne legyen probl�ma, ha olyat t�rl�nk, ami nem hozz� tartozik
    Eszkoz* clone() const;

    //dtor
    virtual ~Erzekelo();

};

#endif // ERZEKELO_H_INCLUDED
