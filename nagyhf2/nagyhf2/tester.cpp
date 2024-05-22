#include <string.h>

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
    jo = test_string();

    if (jo) {
        sik++;
    }

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

    ossz++;
    jo = test_logika();

    if (jo) {
        sik++;
    }

    ossz++;
    jo = test_szirena();

    if (jo) {
        sik++;
    }

    std::cout << "Sikeres / összes: " << sik << "/" << ossz << "\n\n";
    return sik == ossz;
}

bool test_string() {

    std::cout << "String osztály tesztelése:\n";

    String asd("asd");

    if (strcmp(asd.c_str(), "asd")) {
        std::cout << "Hiba történt: Konstruktor vagy getter hiba!\n\n";
        return false;
    }

    String as('a');

    if (strcmp(as.c_str(), "a")) {
        std::cout << "Hiba történt: Karakter konstruktor hiba!\n\n";
        return false;
    }

    if (asd != "asd" || asd == "asf") {
        std::cout << "Hiba történt: == vagy != operátor hiba!\n\n";
        return false;
    }

    if (asd.size() != 3) {
        std::cout << "Hiba történt: Méret lekérdezés hiba!\n\n";
        return false;
    }

    if (asd.size() != 3) {
        std::cout << "Hiba történt: Méret lekérdezés hiba!\n\n";
        return false;
    }

    asd = "as";

    if (strcmp(asd.c_str(), "as")) {
        std::cout << "Hiba történt: Értékadó operátor hiba!\n\n";
        return false;
    }

    asd += 'd';

    if (strcmp(asd.c_str(), "asd")) {
        std::cout << "Hiba történt: += operátor hiba!\n\n";
        return false;
    }

    asd--;

    if (strcmp(asd.c_str(), "as")) {
        std::cout << "Hiba történt: -- operátor hiba!\n\n";
        return false;
    }

    std::cout << "String osztály müködik.\n\n";
    return true;

}

bool test_kodolv(){

    std::cout << "Kodolvaso osztály tesztelése:\n";

    Kodolvaso kod1("asd"), kod2("asdf",1234);

    if (kod1.getnev() != "asd" || kod1.getert() != 0 || kod1.igaze() != false || kod2.getnev()!= "asdf" || kod2.getert() != 1234 || kod2.igaze() != false) {
        std::cout << "Hiba történt: Construktor vagy getter hiba!\n\n";
        return false;
    }

    Kodolvaso alap;

    if (alap.getnev() != "" || alap.getert() != 0 || alap.igaze() != false) {
        std::cout << "Hiba történt: Paraméter nélküli konstruktor hiba!\n\n";
        return false;
    }

    kod1.setnev("asd2");
    kod1.setert(123);

    if (kod1.getnev() != "asd2" || kod1.getert() != 123) {
        std::cout << "Hiba történt: Setter hiba!\n\n";
        return false;
    }

    kod1.beut(123);

    if (!kod1.igaze()) {
        std::cout << "Hiba történt: Beütés vagy annak lekérése hibás!\n\n";
        return false;
    }

    kod1.aktival();

    if (kod1.igaze()) {
        std::cout << "Hiba történt: Újra aktiválás hiba!\n\n";
        return false;
    }

    kod1.beut(124);

    if (kod1.igaze()) {
        std::cout << "Hiba történt: Rossz kódra is nyit!\n\n";
        return false;
    }

    Kodolvaso* clon = kod1.clone();

    if (clon->getnev() != "asd2" || clon->getert() != 123) {
        std::cout << "Hiba történt: Setter hiba!\n\n";
        return false;
    }

    delete clon;

    std::cout << "Kodolvaso osztály müködik.\n\n";
    return true;
}

bool test_erztipus() {

    std::cout << "ErzTipus osztály tesztelése:\n";

    ErzTipus erz("asd",20,40,0);

    if (erz.getnev() != "asd" || erz.getalap() != 20 || erz.getalso() != 0 || erz.getfelso()!= 40) {
        std::cout << "Hiba történt: Construktor vagy getter hiba!\n\n";
        return false;
    }

    ErzTipus alap;

    if (alap.getnev() != "" || alap.getalap() != 0 || alap.getalso() != 0 || alap.getfelso()!= 0) {
        std::cout << "Hiba történt: Paraméter nélküli konstruktor hiba!\n\n";
        return false;
    }

    erz.setnev("asd2");
    erz.setalap(12);
    erz.setalso(10);
    erz.setfelso(20);

    if (erz.getnev() != "asd2" || erz.getalap() != 12 || erz.getalso() != 10 || erz.getfelso() != 20) {
        std::cout << "Hiba történt: Setter hiba!\n\n";
        return false;
    }

    std::cout << "ErzTipus osztály müködik.\n\n";
    return true;
}

bool test_erzekelo() {

    std::cout << "Erzekelo osztály tesztelése:\n";

    ErzTipus temp("retek", 15, 10, 20), hmero("Homerseklet", 23, 50, -15);

    Erzekelo esz("asd", temp);

    if (esz.getnev() != "asd" || esz.gettip() != Erzek || esz.getert() != 15 || esz.geterztip().getnev() != "retek") {
        std::cout << "Hiba történt: Construktor vagy getter hiba!\n\n";
        return false;
    }

    Erzekelo alap;

    if (alap.getnev() != "" || alap.gettip() != Erzek || alap.getert() != 0 || alap.geterztip().getnev() != "") {
        std::cout << "Hiba történt: Paraméter nélküli konstruktor hiba!\n\n";
        return false;
    }

    esz.setnev("asd2");
    esz.seterztip(hmero);

    if (esz.getnev() != "asd2" || esz.getert() != 23 || esz.geterztip().getnev() != "Homerseklet" ) {
        std::cout << "Hiba történt: Setter hiba!\n\n";
        return false;
    }

    esz.setert(25);

    if (esz.getert() != 25) {
        std::cout << "Hiba történt: Setter hiba!\n\n";
        return false;
    }

    if (esz.igaze()){
        std::cout << "Hiba történt: Jelzési hiba!\n\n";
        return false;
    }

    esz.setert(50);

    if (!esz.igaze()){
        std::cout << "Hiba történt: Jelzési hiba!\n\n";
        return false;
    }

    esz.setert(-16);

    if (!esz.igaze()){
        std::cout << "Hiba történt: Jelzési hiba!\n\n";
        return false;
    }

    Erzekelo *cl = esz.clone();

    if (cl->getnev() != "asd2" || cl->gettip() != Erzek || cl->getert() != -16 || cl->geterztip().getnev() != "Homerseklet" || cl->igaze() != true) {
        std::cout << "Hiba történt: Klónozás hiba!\n\n";
        return false;
    }

    delete cl;

    std::cout << "Eszkoz osztály müködik.\n\n";
    return true;
}

bool test_logika() {

    std::cout << "Logika osztály tesztelése:\n";

    ErzTipus erz("Homero",20,40,0);
    Erzekelo nappali("nappali", erz), halo("halo", erz);
    Logika logik("Logika", idozito, nappali.clone());

    if (logik.getnev() != "Logika" || logik.getidoz() != 0 || logik.gettip() != Logik || logik.size() != 1 || logik.getelem(0)->getnev() != "nappali") {
        std::cout << "Hiba történt: Construktor vagy getter hiba!\n\n";
        return false;
    }

    Logika alap;

    if (alap.getnev() != "" || alap.getidoz() != 0 || alap.gettip() != Logik || alap.size() != 1 || alap.getelem(0)->getnev() != "" || alap.getltip() != es) {
        std::cout << "Hiba történt: Paraméter nélküli konstruktor hiba!\n\n";
        return false;
    }

    logik.setidoz(100);

    if (logik.getidoz() != 100) {
        std::cout << "Hiba történt: setter hiba!\n\n";
        return false;
    }

    nappali.setert(50);
    logik.rep(nappali.clone(), 0);

    if (logik.igaze(0)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(idoz/nem járt le)\n\n";
        return false;
    }

    if (!logik.igaze(100)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(idoz/lejárt és igaz)\n\n";
        return false;
    }

    logik.reset();
    logik.setltip(nem);
    nappali.setert(20);
    logik.rep(nappali.clone(), 0);

    if (logik.igaze(0)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(nem/nem járt le)\n\n";
        return false;
    }

    if (!logik.igaze(100)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(nem/lejárt és hamis)\n\n";
        return false;
    }

    logik.setltip(es);
    nappali.setert(50);
    halo.setert(25);
    logik.rep(nappali.clone(), 0);
    logik.add(halo.clone());
    logik.reset();
    logik.igaze(0);

    if (logik.igaze(100)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(es/lejárt és egyik hamis)\n\n";
        return false;
    }

    nappali.setert(25);
    logik.rep(nappali.clone(), 0);
    logik.reset();
    logik.igaze(0);

    if (logik.igaze(100)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(es/lejárt és mind hamis)\n\n";
        return false;
    }

    nappali.setert(50);
    halo.setert(50);
    logik.rep(nappali.clone(), 0);
    logik.rep(halo.clone(), 1);
    logik.reset();
    logik.igaze(0);

    if (!logik.igaze(100)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(es/lejárt és mind igaz)\n\n";
        return false;
    }

    logik.setltip(vagy);
    nappali.setert(50);
    halo.setert(25);
    logik.rep(nappali.clone(), 0);
    logik.rep(halo.clone(), 1);
    logik.reset();
    logik.igaze(0);

    if (!logik.igaze(100)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(vagy/lejárt és egyik hamis)\n\n";
        return false;
    }

    nappali.setert(25);
    logik.rep(nappali.clone(), 0);
    logik.reset();
    logik.igaze(0);

    if (logik.igaze(100)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(vagy/lejárt és mind hamis)\n\n";
        return false;
    }

    nappali.setert(50);
    halo.setert(50);
    logik.rep(nappali.clone(), 0);
    logik.rep(halo.clone(), 1);
    logik.reset();
    logik.igaze(0);

    if (!logik.igaze(100)) {
        std::cout << "Hiba történt: Igazság lekérdezés hiba!(vagy/lejárt és mind igaz)\n\n";
        return false;
    }

    logik.add(logik.clone());
    logik.setltip(es);
    logik.reset();
    logik.igaze(0);

    if (logik.getelem(2)->getnev() != "Logika" || logik.getelem(2)->gettip() != Logik || !logik.igaze(100)){
        std::cout << "Hiba történt: Klónozás hiba!\n\n";
        return false;
    }

    logik.del(1);

    if (!logik.igaze(100)) {
        std::cout << "Hiba történt: Elem törlése hiba!(vagy/lejárt és mind igaz)\n\n";
        return false;
    }

    std::cout << "Logika osztály müködik.\n\n";
    return true;

}

bool test_szirena() {

    std::cout << "Szirena osztály tesztelése:\n";

    ErzTipus erz("Homero",20,40,0);
    Erzekelo nappali("nappali", erz);
    Logika logik("Logika", idozito, nappali.clone());
    Kodolvaso olv("Billenty", 1234);
    Szirena jelzo("Riaszt", &logik, 100, &olv);

    if (jelzo.getnev() != "Riaszt" || jelzo.getidoz() != 100 || jelzo.getlogika()->getnev() != "Logika" || jelzo.getolvas()->getnev() != "Billenty") {
        std::cout << "Hiba történt: Konstruktor vagy getter hiba!\n\n";
        return false;
    }

    Szirena alap0;

    if (alap0.getnev() != "" || alap0.getidoz() != 0 || alap0.getlogika() != 0 || alap0.getolvas() != 0) {
        std::cout << "Hiba történt: Paraméter nélküli konstruktor hiba!\n\n";
        return false;
    }

    nappali.setert(50);
    logik.rep(nappali.clone(), 0);
    jelzo.getall(0);

    if (jelzo.getall(100) != szamlal) {
        std::cout << "Hiba történt: Számlál hiba!\n\n";
        return false;
    }

    if (jelzo.getall(200) != riaszt) {
        std::cout << "Hiba történt: Riasztás hiba!\n\n";
        return false;
    }

    olv.beut(1234);

    if (jelzo.getall(300) != alap) {
        std::cout << "Hiba történt: Kódolvasó hiba!\n\n";
        return false;
    }

    olv.aktival();

    if (jelzo.getall(300) != szamlal) {
        std::cout << "Hiba történt: Újraaktiválás hiba!\n\n";
        return false;
    }

    if (jelzo.getall(400) != riaszt) {
        std::cout << "Hiba történt: Újrariasztás hiba!\n\n";
        return false;
    }

    std::cout << "Szirena osztály müködik.\n\n";
    return true;

}











