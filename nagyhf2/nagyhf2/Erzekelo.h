#include "Eszkoz.h"
#include "Tipus.h"

#ifndef ERZEKELO_H_INCLUDED
#define ERZEKELO_H_INCLUDED

class Erzekelo :public Eszkoz {
    int ertek;
    ErzTipus tipus;
public:
    //ctor
    Erzekelo(const std::string nev, const ErzTipus tipbe);

    //Új érték beállítása
    //ujert: az új érték
    void setert(const int ujert);

    //Érték lekérdezése
    int getert() const;

    //Visszaadja, hogy jelez-e az érzékelõ
    bool igaze();

    //klónozás, a kollekcióhoz, illetve a szirénánál meg hasonlóknál ne legyen probléma, ha olyat törlünk, ami nem hozzá tartozik
    Eszkoz* clone() const;

    //dtor
    ~Erzekelo();

};

#endif // ERZEKELO_H_INCLUDED
