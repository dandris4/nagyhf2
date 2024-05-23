#include "Logika.h"


    Logika::Logika(const String& nevbe, const LogikaTipus be, Eszkoz* eszbe) :Eszkoz(nevbe, Logik) {
        tip = be;
        len = 1;
        visszakezd = -1;
        idozites = 0;
        lista = new Eszkoz*[1];
        lista[0] = eszbe;
    }

    Logika::Logika(const Logika& logbe) :Eszkoz(logbe){

        tip = logbe.tip;
        len = logbe.len;
        visszakezd = logbe.visszakezd;
        idozites = logbe.idozites;
        lista = new Eszkoz*[len];
        for (size_t i = 0; i < len; i++)
            lista[i] = logbe.lista[i]->clone();

    }

    size_t Logika::size() const {
        return len;
    }

    void Logika::add (Eszkoz* elem) {
        if (tip == nem || tip == idozito)
            throw "Max 1 eleme lehet.";
        len++;
        Eszkoz** temp = new Eszkoz*[len];
        for (size_t i = 0; i < len - 1; i++)
            temp[i] = lista[i];
        temp[len - 1] = elem;
        if (lista != nullptr)
            delete[] lista;
        lista = temp;
    }

    void Logika::rep (Eszkoz* elem, size_t idx) {
        if (idx > len)
            throw "Indexeles hiba!";
        delete lista[idx];
        lista[idx] = elem;
    }

    Eszkoz* Logika::getelem (size_t index) {
        return lista[index];
    }

    void Logika::del (const size_t index) {
        if (index >= len || len == 1)
            throw "Tulindexelt vagy 1 elemu lista.";
        Eszkoz** temp = new Eszkoz*[len - 1];
        size_t tlen = 0;
        for (size_t i = 0; i < len ; i++) {
            if (i != index) {
                temp[tlen] = lista[i];
                tlen++;
            }
        }
        len--;
        delete lista[index];
        delete[] lista;
        lista = temp;
    }

    void Logika::setidoz (const int be) {
        idozites = be;
    }

    void Logika::setltip (const LogikaTipus be) {
        tip = be;
    }

    LogikaTipus Logika::getltip() const {
        return tip;
    }

    int Logika::getidoz () const{
        return idozites;
    }

    bool Logika::igaze (int ido) {
        bool ret;
        switch(tip) {
            case idozito:
                if (lista[0]->igaze(ido)) {
                    ret = true;
                    break;
                }
                visszakezd = -1;
                ret = false;
            break;
            case nem:
                if (!lista[0]->igaze(ido)) {
                    ret = true;
                    break;
                }
                visszakezd = -1;
                ret = false;
            break;
            case es:
                ret = true;
                for (size_t i = 0; i < len; i++)
                    if (!lista[i]->igaze(ido)) {
                        visszakezd = -1;
                        ret = false;
                    }
            break;
            case vagy:
                for (size_t i = 0; i < len; i++)
                    if (lista[i]->igaze(ido)) {
                        ret = true;
                        break;
                    }
                if (!ret) {
                    visszakezd = -1;
                    ret = false;
                }
            break;
        }
        if (ret && visszakezd == -1 && idozites == 0)
            return true;
        if (ret && visszakezd == -1) {
            visszakezd = ido;
            return ido - visszakezd > idozites;

        }
        if (ret && ido - visszakezd <= idozites) {
            return true;
        }
        if (!ret) {
            visszakezd = -1;
            return false;
        }

        throw "Hiba";
    }

    void Logika::reset() {
        visszakezd = -1;
    }

    Logika* Logika::clone() const {
        Logika *uj = new Logika(*this);
        return uj;
    }

    Logika::~Logika() {
        for (size_t i = 0; i < len; i++)
            delete lista[i];

        delete[] lista;
    }
