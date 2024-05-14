#include "Eszkoz.h"

#include "memtrace.h"

    Eszkoz::Eszkoz(const String &be, const eszkoztip tipbe) :nev(be), esztip(tipbe) {}

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


