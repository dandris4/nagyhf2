
#ifndef ESZKOZOK_H
#define ESZKOZOK_H

enum eszkoztip {
    Erzek, Logik
};

class Eszkoz {
    std::string nev;
    eszkoztip esztip;
public:
    //ctor
    Eszkoz(const std::string &be, const eszkoztip tipbe);

    //név beállítása
    virtual void setnev(const std::string &nevbe);

    //név lekérdezése
    virtual std::string getnev() const;

    //Visszaadja, hogy igaz-e az eszköz
    virtual bool igaze(int ido);

    //klónozás, a kollekcióhoz, illetve a szirénánál meg hasonlóknál ne legyen probléma, ha olyat törlünk, ami nem hozzá tartozik
    virtual Eszkoz* clone() const;

    //dtor
    virtual ~Eszkoz();
};

#endif // ESZKOZOK_H
