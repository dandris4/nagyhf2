#include "Szirena.h"

    Szirena::Szirena(const String &be, Logika* krbe, const int idoz, Kodolvaso* olvbe)  :nev(be), krit(krbe), visszakezd(-1), idozites(idoz), olvaso(olvbe) {}

    Szirena::Szirena() {
        nev = "";
        krit = 0;
        olvaso = 0;
        visszakezd = -1;
        idozites = 0;
    }

    void Szirena::setnev(const String &nevbe) {
        nev = nevbe;
    }

    void Szirena::setlogika(Logika* uj) {
        krit = uj;
    }

    void Szirena::setidoz(const int be) {
        idozites = be;
    }

    void Szirena::setolvas(Kodolvaso* be) {
        olvaso = be;
    }

    Logika* Szirena::getlogika() const {
        return krit;
    }

    String Szirena::getnev() const{
        return nev;
    }

    int Szirena::getidoz() const {
        return idozites;
    }

    Kodolvaso* Szirena::getolvas() const {
        return olvaso;
    }

    szirall Szirena::getall(const int ido) {
        bool ret = krit->igaze(ido);
        if (olvaso->igaze()) {
            visszakezd = -1;
            return alap;
        }
        if (ret && visszakezd == -1 && idozites == 0)
            return riaszt;
        if (ret && ido - visszakezd <= idozites) {
            return riaszt;
        }
        if (ret) {
            visszakezd = ido;
            return szamlal;
        }
        if (!ret) {
            visszakezd = -1;
            return alap;
        }

        throw "Hiba";
    }

    Szirena::~Szirena() {
    }
