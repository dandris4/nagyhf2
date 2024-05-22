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

    //m�ret lek�r�s
    size_t size() const;

    //List�hoz f�z�s
    //elem: �j elem
    void add (Eszkoz* elem);

    //elem csere
    void rep (Eszkoz* elem, size_t idx);

    //A lista egyik elem�nek lek�r�se
    //index: lek�rend� elem indexe
    Eszkoz* getelem (size_t index);

    //A lista egyik elem�nek kit�rl�se
    //index: t�rlend� elem indexe
    void del (const size_t index);

    //Id�z�t� be�ll�t�sa
    //be: �j id�
    void setidoz (const int be);

    //t�pus be�ll�t�sa
    void setltip (const LogikaTipus be);

    //t�pus lek�rdez�se
    LogikaTipus getltip() const;

    //Id�z�t� lek�rdez�se
    //return: id�z�t� m�rete
    int getidoz () const;

    //Visszaadja, hogy igaz-e a logika, illetve az id�z�t�st kezeli
    //return: igaz, ha a logika teljes�l
    bool igaze (int ido);

    //reset
    void reset();

    //kl�n
    Logika* clone() const;

    // �rt�kad� oper�tor.
    Logika& operator=(const Logika& rhs_l);

    //dtor
    virtual ~Logika();
};

#endif // LOGIKA_H_INCLUDED
