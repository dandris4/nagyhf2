#ifndef SZIRENA_H_INCLUDED
#define SZIRENA_H_INCLUDED

#include "Logika.h"
#include "Kodolvaso.h"

enum szirall {
    alap, szamlal, riaszt
};

class Szirena {
    std::string nev;
    Logika* krit;
    int visszakezd,idozites;
    Kodolvaso* olvaso;
public:
    //ctor
    //be: sziréna neve
    Szirena(std::string &be);

    //Név beállítása
    //nevbe: új név
    void setnev(std::string &nevbe);

    //logka beállítása
    //uj: új logika, dinamikusan foglalt
    void setlogika(Logika* uj);

    //Időzítés beállítása
    //be: új időzítés
    void setidoz(const int be);

    //olvasó beállítása
    //be: új olvasó
    void setolvas(Kodolvaso* be);

    //Visszaadja a jelenlegi logikát
    //return: krit
    Logika* getlogika() const;

    //Visszaadja a jelenlegi nevet
    //return: nev
    std::string& getnev() const;

    //Visszaadja a jelenlegi időzítést
    //return: idozites
    int getidoz() const;

    //Visszaadja a jelenlegi olvasó pointerkjét
    //return: olvaso
    Kodolvaso* getolvas() const;

    //állapotot ad vissza, ez kezeli az időzítést is
    //return alap, ha nem riaszt, szamlal, ha bekapcsolt, de még nem szól, riaszt, ha letelt az idõzítés, és riaszt
    szirall getall() const;

    //dtor
    virtual ~Szirena();
};

#endif // SZIRENA_H_INCLUDED
