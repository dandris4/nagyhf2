#include "Eszkoz.h"

#include "memtrace.h"

    Eszkoz::Eszkoz(const String &be, const eszkoztip tipbe) :nev(be), esztip(tipbe) {}

    Eszkoz::Eszkoz(const Eszkoz& regi) {
        nev = regi.nev;
        esztip = regi.esztip;
    }

    void Eszkoz::setnev(const String &nevbe) {
        nev = nevbe;
    }

    eszkoztip Eszkoz::gettip() const {
        return esztip;
    }

    String Eszkoz::getnev() const {
        return nev;
    }

    Eszkoz::~Eszkoz() {}


