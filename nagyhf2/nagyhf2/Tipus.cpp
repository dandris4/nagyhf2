#include "Tipus.h"

#include "memtrace.h"


    ErzTipus::ErzTipus(const String &sbe, const int alpbe, const int felsbe, const int alsbe)
        :nev(sbe), alapert(alpbe), also(alsbe), felso(felsbe) {}

    void ErzTipus::setnev(const String &nevbe) {
        nev = nevbe;
    }

    void ErzTipus::setalap(const int erbe) {
        alapert = erbe;
    }

    void ErzTipus::setalso(const int erbe) {
        also = erbe;
    }

    void ErzTipus::setfelso(const int erbe) {
        felso = erbe;
    }

    ErzTipus ErzTipus::operator=(const ErzTipus& rhs_t) {
        if (this != &rhs_t) {
            nev = rhs_t.nev;
            alapert = rhs_t.alapert;
            also = rhs_t.also;
            felso = rhs_t.felso;
        }
        return *this;
    }

    String ErzTipus::getnev() const {
        return nev;
    }

    int ErzTipus::getalap() const {
        return alapert;
    }

    int ErzTipus::getalso() const {
        return also;
    }

    int ErzTipus::getfelso() const {
        return felso;
    }
