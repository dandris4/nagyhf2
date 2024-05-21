#include "Erzekelo.h"

#include "memtrace.h"

    Erzekelo::Erzekelo(const String &nevbe, const ErzTipus tipbe) :Eszkoz(nevbe, Erzek), tipus(tipbe) {
        ertek = tipus.getalap();
    }

    Erzekelo::Erzekelo(const String &nev) :Eszkoz(nev, Erzek), tipus(){
        ertek = tipus.getalap();
    }

    void Erzekelo::setert(const int ujert) {
        ertek = ujert;
    }

    void Erzekelo::seterztip(const ErzTipus ujerz) {
        tipus = ujerz;
        ertek = tipus.getalap();
    }

    ErzTipus Erzekelo::geterztip() const {
        return tipus;
    }

    int Erzekelo::getert() const {
        return ertek;
    }

    bool Erzekelo::igaze(int ido) {
        return (tipus.getalso() >= ertek || tipus.getfelso() <= ertek);
    }

    Erzekelo* Erzekelo::clone() const {
        Erzekelo* uj = new Erzekelo(getnev(), tipus);
        uj->ertek = ertek;
        return uj;
    }

