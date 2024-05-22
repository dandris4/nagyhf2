#ifndef LOGIKA_H_INCLUDED
#define LOGIKA_H_INCLUDED

#include "Eszkoz.h"

#include "memtrace.h"

enum LogikaTipus {
    es,vagy,nem,idozito
};

class Logika :public Eszkoz {
    LogikaTipus tip;
    size_t len;
    Eszkoz** lista;
    int visszakezd,idozites;
public:
    //ctor
    Logika(const String& nevbe = "", const LogikaTipus be = es);

    //ctor
    Logika(const String& nevbe, const LogikaTipus be, Eszkoz* eszbe);

    //mktor
    Logika(const Logika& logbe);

    //méret lekérés
    size_t size() const;

    //Listához füzés
    //elem: új elem
    void add (Eszkoz* elem);

    //elem csere
    void rep (Eszkoz* elem, size_t idx);

    //A lista egyik elemének lekérése
    //index: lekérendö elem indexe
    Eszkoz* getelem (size_t index);

    //A lista egyik elemének kitörlése
    //index: törlendö elem indexe
    void del (const size_t index);

    //Idözítö beállítása
    //be: új idö
    void setidoz (const int be);

    //típus beállítása
    void setltip (const LogikaTipus be);

    //típus lekérdezése
    LogikaTipus getltip() const;

    //Idözítö lekérdezése
    //return: idözítö mérete
    int getidoz () const;

    //Visszaadja, hogy igaz-e a logika, illetve az idözítést kezeli
    //return: igaz, ha a logika teljesül
    bool igaze (int ido);

    //reset
    void reset();

    //klón
    Logika* clone() const;

    // Értékadó operátor.
    Logika& operator=(const Logika& rhs_l);

    //dtor
    virtual ~Logika();
};

#endif // LOGIKA_H_INCLUDED
