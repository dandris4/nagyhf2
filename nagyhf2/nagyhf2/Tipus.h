
#ifndef TIPUS_H_INCLUDED
#define TIPUS_H_INCLUDED

class ErzTipus {
    std::string nev;
    int alapert, also, felso;
public:
    //ctor
    ErzTipus(const std::string &sbe, const int alpbe, const int felsbe, const int alsbe);

    //név beállítása
    //nevbe: új név
    void setnev(const std::string nevbe);

    //alap érték beállítása
    //erbe: új érték
    void setalap(const int erbe);

    //alsó határérték beállítása
    //erbe: új érték
    void setalso(const int erbe);

    //felsõ határérték beállítása
    //erbe: új érték
    void setfelso(const int erbe);

    //név lekérése
    //return név
    std::string getnev() const;

    //alap érték lekérése
    //return érték
    int getalap() const;

    //alsó határérték lekérése
    //return érték
    int getalso() const;

    //felsõ határérték lekérése
    //return érték
    int getfelso() const;

    //dtor
    ~ErzTipus();
};


#endif // TIPUS_H_INCLUDED
