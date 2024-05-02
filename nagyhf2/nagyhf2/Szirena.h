
#include "Logika.h"

#ifndef SZIRENA_H_INCLUDED
#define SZIRENA_H_INCLUDED

enum szirall {
    alap, szamlal, riaszt
};

class Szirena {
    std::string nev;
    Logika* krit;
    int visszakezd,idozites;
public:
    //ctor
    Szirena(std::string &be);

    //logka beállítása
    //uj: új logika, dinamikusan foglalt
    void setlogika(Logika* uj);

    //Visszaadja a jelenlegi logikát
    //return: krit
    Logika* getlogika();

    //állapotot ad vissza, ez kezeli az időzítést is
    //return alap, ha nem riaszt, szamlal, ha bekapcsolt, de még nem szól, riaszt, ha letelt az idõzítés, és riaszt
    szirall getall();

    //dtor
    ~Szirena();
};

#endif // SZIRENA_H_INCLUDED
