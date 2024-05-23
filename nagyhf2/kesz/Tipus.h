#ifndef TIPUS_H_INCLUDED
#define TIPUS_H_INCLUDED

#include <iostream>

#include "memtrace.h"
#include "String.h"

struct ErzTipus {
    String nev;
    int alapert, also, felso;
public:
    //ctor
    ErzTipus(const String &sbe, const int alpbe, const int felsbe, const int alsbe);

    //n�v be�ll�t�sa
    //nevbe: �j n�v
    void setnev(const String &nevbe);

    //alap �rt�k be�ll�t�sa
    //erbe: �j �rt�k
    void setalap(const int erbe);

    //als� hat�r�rt�k be�ll�t�sa
    //erbe: �j �rt�k
    void setalso(const int erbe);

    //fels� hat�r�rt�k be�ll�t�sa
    //erbe: �j �rt�k
    void setfelso(const int erbe);

    //n�v lek�r�se
    //return n�v
    String getnev() const;

    //alap �rt�k lek�r�se
    //return �rt�k
    int getalap() const;

    //als� hat�r�rt�k lek�r�se
    //return �rt�k
    int getalso() const;

    //fels� hat�r�rt�k lek�r�se
    //return �rt�k
    int getfelso() const;
};


#endif // TIPUS_H_INCLUDED
