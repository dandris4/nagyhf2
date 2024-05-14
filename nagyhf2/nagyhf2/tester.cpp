#include "Erzekelo.h"
#include "Eszkoz.h"
#include "Szirena.h"
#include "Tipus.h"
#include "Logika.h"
#include "Kodolvaso.h"

#include "tester.h"

#include "memtrace.h"

bool test_all() {

    bool jo = true;
    int sik = 0, ossz = 0;;

    ossz++;
    jo = test_kodolv();

    if (jo) {
        sik++;
    }

    ossz++;
    jo = test_erztipus();

    if (jo) {
        sik++;
    }

    ossz++;
    jo = test_erzekelo();

    if (jo) {
        sik++;
    }


    std::cout << "Sikeres / �sszes: " << sik << "/" << ossz << "\n\n";
    return sik == ossz;
}


bool test_kodolv(){

    std::cout << "Kodolvaso oszt�ly tesztel�se:\n";

    Kodolvaso kod1("asd"), kod2("asdf",1234);

    if (kod1.getnev() != "asd" || kod1.getert() != 0 || kod1.igaze() != false || kod2.getnev()!= "asdf" || kod2.getert() != 1234 || kod2.igaze() != false) {
        std::cout << "Hiba t�rt�nt: Construktor vagy getter hiba!\n\n";
        return false;
    }

    kod1.setnev("asd2");
    kod1.setert(123);

    if (kod1.getnev() != "asd2" || kod1.getert() != 123) {
        std::cout << "Hiba t�rt�nt: Setter hiba!\n\n";
        return false;
    }

    kod1.beut(123);

    if (!kod1.igaze()) {
        std::cout << "Hiba t�rt�nt: Be�t�s vagy annak lek�r�se hib�s!\n\n";
        return false;
    }

    kod1.aktival();

    if (kod1.igaze()) {
        std::cout << "Hiba t�rt�nt: �jra aktiv�l�s hiba!\n\n";
        return false;
    }

    kod1.beut(124);

    if (kod1.igaze()) {
        std::cout << "Hiba t�rt�nt: Rossz k�dra is nyit!\n\n";
        return false;
    }

    std::cout << "Kodolvaso oszt�ly m�k�dik.\n\n";
    return true;
}


bool test_erztipus() {

    std::cout << "ErzTipus oszt�ly tesztel�se:\n";

    ErzTipus erz("asd",20,40,0);

    if (erz.getnev() != "asd" || erz.getalap() != 20 || erz.getalso() != 0 || erz.getfelso()!= 40) {
        std::cout << "Hiba t�rt�nt: Construktor vagy getter hiba!\n\n";
        return false;
    }

    erz.setnev("asd2");
    erz.setalap(12);
    erz.setalso(10);
    erz.setfelso(20);

    if (erz.getnev() != "asd2" || erz.getalap() != 12 || erz.getalso() != 10 || erz.getfelso() != 20) {
        std::cout << "Hiba t�rt�nt: Setter hiba!\n\n";
        return false;
    }

    std::cout << "ErzTipus oszt�ly m�k�dik.\n\n";
    return true;
}

bool test_erzekelo() {

    std::cout << "Erzekelo oszt�ly tesztel�se:\n";

    ErzTipus temp("retek", 15, 10, 20), hmero("Homerseklet", 23, 50, -15);

    Erzekelo esz("asd", temp);

    if (esz.getnev() != "asd" || /*esz.gettip() != Erzek ||*/ esz.getert() != 15 || esz.geterztip().getnev() != "retek") {
        std::cout << "Hiba t�rt�nt: Construktor vagy getter hiba!\n\n";
        return false;
    }

    esz.setnev("asd2");
    esz.seterztip(hmero);

    if (esz.getnev() != "asd2" || esz.getert() != 23 || esz.geterztip().getnev() != "Homerseklet" ) {
        std::cout << "Hiba t�rt�nt: Setter hiba!\n\n";
        return false;
    }

    esz.setert(25);

    if (esz.getert() != 25) {
        std::cout << "Hiba t�rt�nt: Setter hiba!\n\n";
        return false;
    }

    if (esz.igaze()){
        std::cout << "Hiba t�rt�nt: Jelz�si hiba!\n\n";
        return false;
    }

    esz.setert(50);

    if (!esz.igaze()){
        std::cout << "Hiba t�rt�nt: Jelz�si hiba!\n\n";
        return false;
    }

    esz.setert(-16);

    if (!esz.igaze()){
        std::cout << "Hiba t�rt�nt: Jelz�si hiba!\n\n";
        return false;
    }

    Erzekelo *cl = esz.clone();

    if (cl->getnev() != "asd2" || cl->gettip() != Erzek || cl->getert() != 23 || cl->geterztip().getnev() != "Homerseklet" || cl->igaze() != false) {
        std::cout << "Hiba t�rt�nt: Kl�noz�s hiba!\n\n";
        return false;
    }

    delete cl;

    std::cout << sizeof(Erzekelo);

    std::cout << "Eszkoz oszt�ly m�k�dik.\n\n";
    return true;
}
