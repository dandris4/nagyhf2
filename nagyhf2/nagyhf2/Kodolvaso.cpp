#include "Kodolvaso.h"

#include "memtrace.h"


    Kodolvaso::Kodolvaso(const String &nevbe, const int erbe) :nev(nevbe), ertek(erbe), jokod(false) {}

    void Kodolvaso::setnev(const String &nevbe) {
        nev = nevbe;
    }

    void Kodolvaso::setert(const int erbe) {
        ertek = erbe;
    }

    String Kodolvaso::getnev() const {
        return nev;
    }

    int Kodolvaso::getert() const {
        return ertek;
    }

    bool Kodolvaso::beut(const int kod) {
        jokod = kod == ertek;
        return jokod;
    }

    void Kodolvaso::aktival() {
        jokod = false;
    }

    bool Kodolvaso::igaze() {
        return jokod;
    }

    Kodolvaso::~Kodolvaso() {}

