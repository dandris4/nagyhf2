#include "Eszkoz.h"

#include "memtrace.h"

    std::istream& operator>>(std::istream& is, eszkoztip& rhs_l) {
        int i;
        is >> i;
        switch (i) {
            case 0:
                rhs_l = Erzek;
            break;
            case 1:
                rhs_l = Logik;
            break;
        }
        return is;
    }

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


