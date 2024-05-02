
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

    //n�v be�ll�t�sa
    virtual void setnev(const std::string &nevbe);

    //n�v lek�rdez�se
    virtual std::string getnev() const;

    //Visszaadja, hogy igaz-e az eszk�z
    virtual bool igaze(int ido);

    //kl�noz�s, a kollekci�hoz, illetve a szir�n�n�l meg hasonl�kn�l ne legyen probl�ma, ha olyat t�rl�nk, ami nem hozz� tartozik
    virtual Eszkoz* clone() const;

    //dtor
    virtual ~Eszkoz();
};

#endif // ESZKOZOK_H
