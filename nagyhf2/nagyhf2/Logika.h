#include "Eszkoz.h"

#ifndef LOGIKA_H_INCLUDED
#define LOGIKA_H_INCLUDED

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
    Logika(const LogikaTipus be = idozito);

    //Listához fûzés
    //elem: új elem
    void add (Eszkoz* elem);

    //A lista egyik elemének lekérése
    //index: lekérendõ elem indexe
    Eszkoz* getelem (size_t index);

    //A lista egyik elemének kitörlése
    //index: törlendõ elem indexe
    void del (const size_t index);

    //Idõzítõ beállítása
    //be: új idõ
    void setidoz (const int be);

    //Idõzítõ lekérdezése
    //return: idõzítõ mérete
    int getidoz ();

    //Visszaadja, hogy igaz-e a logika, illetve az idõzítést kezeli
    //return: igaz, ha a logika teljesül
    bool igaze (int ido);

    ~Logika();
};

#endif // LOGIKA_H_INCLUDED
