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

    //List�hoz f�z�s
    //elem: �j elem
    void add (Eszkoz* elem);

    //A lista egyik elem�nek lek�r�se
    //index: lek�rend� elem indexe
    Eszkoz* getelem (size_t index);

    //A lista egyik elem�nek kit�rl�se
    //index: t�rlend� elem indexe
    void del (const size_t index);

    //Id�z�t� be�ll�t�sa
    //be: �j id�
    void setidoz (const int be);

    //Id�z�t� lek�rdez�se
    //return: id�z�t� m�rete
    int getidoz ();

    //Visszaadja, hogy igaz-e a logika, illetve az id�z�t�st kezeli
    //return: igaz, ha a logika teljes�l
    bool igaze (int ido);

    ~Logika();
};

#endif // LOGIKA_H_INCLUDED
