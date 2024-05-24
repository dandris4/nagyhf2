#include <iostream>
#include <time.h>
#include "c-econio/econio.h"

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#endif

#include "Erzekelo.h"
#include "Eszkoz.h"
#include "Szirena.h"
#include "Tipus.h"
#include "Logika.h"
#include "Kodolvaso.h"
#include "String.h"

#include "tester.h"

#include "memtrace.h"


bool mentes(String &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Szirena* szirenak, Kodolvaso* kodolvasok, int *elemszam) { //Ha sikerült megnyitni a file-t beleírja az elemeket

    std::ofstream f;
    f.open(filenev.c_str());
    if (!f)
        return false;
    for (size_t i = 0; i < 5; i++)
            f << elemszam[i] << ' ';
    f << '\n';
    for (int i = 0; i < elemszam[2]; i++) { //Érzékelö típusok beírása
        f << tipusok[i].getnev() << ' ' << tipusok[i].getalap() << ' ' << tipusok[i].getalso() << ' ' << tipusok[i].getfelso() << "\n";
    }
    for (int i = 0; i < elemszam[1]; i++) { //Érzékelök beírása
        f << erzekelok[i].getnev() << ' ' << erzekelok[i].geterztip().getnev() << "\n";
    }
    for (int i = 0; i < elemszam[0]; i++) { //Logikák beírása
        f << logikak[i].getnev() << ' ' << logikak[i].getltip() << ' ' << logikak[i].getidoz() << ' ' << logikak[i].size() << "\n";
        for (size_t a = 0; a < logikak[i].size(); a++)
            f << logikak[i].getelem(a)->gettip() << ' ' << logikak[i].getelem(a)->getnev() << "\n";
    }
    for (int i = 0; i < elemszam[4]; i++) { //Kódolvasók beírása
        f << kodolvasok[i].getnev() << ' ' << kodolvasok[i].getert() << "\n";
    }
    for (int i = 0; i < elemszam[3]; i++) { //Szirénák beírása
        f << szirenak[i].getnev() << ' ' << szirenak[i].getlogika()->getnev() << ' ' << szirenak[i].getidoz() << ' ' << szirenak[i].getolvas()->getnev() << "\n";
    }
    f.close();

    return true;
}

bool betoltes(String &filenev, Logika** logikak, Erzekelo** erzekelok, ErzTipus** tipusok, Szirena** szirenak, Kodolvaso** kodolvasok, int *elemszam) {


    std::ifstream f;
    f.open(filenev.c_str());
    if (!f)
        return false;

    int telemszam[5] = {0};

    for (size_t i = 0; i < 5; i++) {
        if(!(f >> telemszam[i]))
            return false;
    }

    Logika* templ;
    Erzekelo* tempe;
    ErzTipus* tempt;
    Szirena* temps;
    Kodolvaso* tempo;


    if (telemszam[0] != 0)
        templ = new Logika[telemszam[0]];
    else
        templ = nullptr;

    if (telemszam[1] != 0)
        tempe = new Erzekelo[telemszam[1]];
    else
        tempe = nullptr;

    if (telemszam[2] != 0)
        tempt = new ErzTipus[telemszam[2]];
    else
        tempt = nullptr;

    if (telemszam[3] != 0)
        temps = new Szirena[telemszam[3]];
    else
        temps = nullptr;

    if (telemszam[4] != 0)
        tempo = new Kodolvaso[telemszam[4]];
    else
        tempo = nullptr;

    for (int i = 0; i < telemszam[2]; i++) { //Érzékelö típusok olvasása
        ErzTipus olv;
        String nev;
        int alap, also, felso;
        if (!(f >> nev >> alap >> also >> felso)) {
            delete[] templ;
            delete[] tempe;
            delete[] tempt;
            delete[] temps;
            delete[] tempo;
            return false;
        }
        olv.setnev(nev);
        olv.setalap(alap);
        olv.setalso(also);
        olv.setfelso(felso);
        tempt[0] = olv;
    }

    for (int i = 0; i < telemszam[1]; i++) { //Érzékelök olvasása
        Erzekelo olv;
        String nev, tip;
        if (!(f >> nev >> tip))  {
            delete[] templ;
            delete[] tempe;
            delete[] tempt;
            delete[] temps;
            delete[] tempo;
            return false;
        }

        olv.setnev(nev);

        for (int a = 0; a < telemszam[2]; a++)
            if (tempt[a].getnev() == tip)
                olv.seterztip(tempt[a]);
        if (olv.geterztip().getnev() == "") {
            delete[] templ;
            delete[] tempe;
            delete[] tempt;
            delete[] temps;
            delete[] tempo;
            return false;
        }

        tempe[i] = olv;
    }

    for (int i = 0; i < telemszam[0]; i++) { //Logikák olvasása
        Logika olv;
        String nev;
        LogikaTipus tip;
        int idoz,len;

        if (!(f >> nev >> tip >> idoz >> len))  {
            delete[] templ;
            delete[] tempe;
            delete[] tempt;
            delete[] temps;
            delete[] tempo;
            return false;
        }

        olv.setnev(nev);
        olv.setltip(tip);
        olv.setidoz(idoz);

        eszkoztip etip;

        for (int a = 0; a < len; a++) { //Elemeinek olvasása
            if (!(f >> etip >> nev))  {
                delete[] templ;
                delete[] tempe;
                delete[] tempt;
                delete[] temps;
                delete[] tempo;
                return false;
            }
            if (etip == Logik)  {
                for (int s = 0; s < i; s++)
                    if (templ[s].getnev() == tip)
                        olv.add(templ[s].clone());
                if (olv.size() < (size_t)a) {
                    delete[] templ;
                    delete[] tempe;
                    delete[] tempt;
                    delete[] temps;
                    delete[] tempo;
                    return false;
                }
            }
            else {
                for (int s = 0; s < elemszam[1]; s++)
                    if (tempe[s].getnev() == tip)
                        olv.add(tempe[s].clone());
                if (olv.size() < (size_t)a) {
                    delete[] templ;
                    delete[] tempe;
                    delete[] tempt;
                    delete[] temps;
                    delete[] tempo;
                    return false;
                }
            }
        }

        templ[i] = olv;

    }

    for (int i = 0; i < telemszam[4]; i++) { //Kódolvasók olvasása
        Kodolvaso olv;
        String nev;
        int ertek;
        if (!(f >> nev >> ertek)) {
            delete[] templ;
            delete[] tempe;
            delete[] tempt;
            delete[] temps;
            delete[] tempo;
            return false;
        }
        olv.setnev(nev);
        olv.setert(ertek);

        tempo[i] = olv;
    }

    for (int i = 0; i < telemszam[3]; i++) { //Szirénák olvasása
        Szirena olv;
        String nev, log, kod;
        int idoz;

        if (!(f >> nev >> log >> idoz >> kod))  {
            delete[] templ;
            delete[] tempe;
            delete[] tempt;
            delete[] temps;
            delete[] tempo;
            return false;
        }

        olv.setnev(nev);
        olv.setidoz(idoz);

        for (int a = 0; a < telemszam[0]; a++)
            if (templ[a].getnev() == log)
                olv.setlogika(&templ[a]);
        if (olv.getlogika()->getnev() == "") {
            delete[] templ;
            delete[] tempe;
            delete[] tempt;
            delete[] temps;
            delete[] tempo;
            return false;
        }

        for (int a = 0; a < telemszam[4]; a++)
            if (tempo[a].getnev() == kod)
                olv.setolvas(&tempo[a]);
        if (olv.getolvas()->getnev() == "") {
            delete[] templ;
            delete[] tempe;
            delete[] tempt;
            delete[] temps;
            delete[] tempo;
            return false;
        }

        temps[i] = olv;
    }


    if (*logikak != nullptr)
        delete[] *logikak;
    if (*erzekelok != nullptr)
        delete[] *erzekelok;
    if (*tipusok != nullptr)
        delete[] *tipusok;
    if (*szirenak != nullptr)
        delete[] *szirenak;
    if (*kodolvasok != nullptr)
        delete[] *kodolvasok;

    *logikak = templ;
    *erzekelok = tempe;
    *tipusok = tempt;
    *szirenak = temps;
    *kodolvasok = tempo;

    for (int i = 0; i < 5; i++)
        elemszam[i] = telemszam[i];

    return true;
}

int getcharwoent () {

    #ifdef _WIN32
        return getch();
    #else
        return getchar();
    #endif // _WIN32


}

bool lenyomtae () {

    #ifdef _WIN32
        return kbhit();
    #else
        return true;
    #endif // _WIN32

}

void jelenlegi(const String& be) { //Kiemeli a bejövö sztringet
    econio_textbackground(COL_WHITE);
    econio_textcolor(COL_BLACK);
    std::cout << be;
    econio_textbackground(COL_BLACK);
    econio_textcolor(COL_WHITE);
}

void logiklistaz(Logika* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilistázza a logikákat a konzolra
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if (ujkiir) {
        if ((size_t)kcurrent == darab)
            jelenlegi("  Új Logika\n");
        else
            std::cout << "  Új Logika\n";
    }
}

void erzlistaz(Erzekelo* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilistázza a érzékelöket a konzolra
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if (ujkiir) {
        if ((size_t)kcurrent == darab)
            jelenlegi("  Új Érzékelö\n");
        else
            std::cout << "  Új Érzékelö\n";
    }
}

void tiplistaz(ErzTipus* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilistázza a típusokat a konzolra
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if (ujkiir) {
        if ((size_t)kcurrent == darab)
            jelenlegi("  Új Típus\n");
        else
            std::cout << "  Új Típus\n";
    }
}

void szirenlistaz(Szirena* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilistázza a szirénákat a konzolra
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if (ujkiir) {
        if ((size_t)kcurrent == darab)
            jelenlegi("  Új Sziréna\n");
        else
            std::cout << "  Új Sziréna\n";
    }
}

void olvlistaz(Kodolvaso* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilistázza az olvasókat a konzolra
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if (ujkiir) {
        if ((size_t)kcurrent == darab)
            jelenlegi("  Új Olvasó\n");
        else
            std::cout << "  Új Olvasó\n";
    }
}

void ltiplistaz(int kcurrent) { //Kilistázza a logika típusokat a konzolra
    char lis[][8 + 1] = {"és\n", "vagy\n", "nem\n", "idözitö\n"};
    for (int i = 0; i < 4; i++) {
        if (kcurrent == i)
            jelenlegi(lis[i]);
        else
            std::cout << lis[i];
    }
}

int main() {

    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif

    std::cout << "Osztályok tesztelése:\n\n";

    test_all();// A tester.cpp összes tesztjét lefuttatja

    std::cout << "Tesztek befejezve.\nKilépéshez vissza gomb, folytatáshoz enter.\n";

    int tveg = getcharwoent();
    while (tveg != 13 && tveg != 8 && tveg != 'b') { //Enterre folytatja, visszagombra vagy b-re kilép
        tveg = getcharwoent();
    }
    int allapot;
    tveg == 13 ? allapot = 0 : allapot = -1;

    int current = 0, //A jelenlegi pozíciót mutat
    ido = 0,         //A szimulációban mutatja az eltelt idöt
    kcurrent = -1,   //A lenyitott állapotban mutatja, hogy melyik elem van kijelölve
    alkcurrent = -1,    //Egy elem szerkesztésekor mutatja, hogy melyik elem van kijelölve
    elemszam[5] = {0};  //Megmondja, hogy milyen típusú elemböl mennyi van (Logika, érzékelö, típus, sziréna, kódolvasó)
    bool stpmegy = false, lenyit[5] = {0};
    String filenev("");
    Logika* logikak = nullptr;
    Erzekelo* erzekelok = nullptr;
    ErzTipus* tipusok = nullptr;
    Szirena* szirenak = nullptr;
    Kodolvaso* kodolvasok = nullptr;
    bool ir = false;

    Logika templ;
    Erzekelo tempe;
    ErzTipus tempt;
    Szirena  temps;
    Kodolvaso tempo;

    econio_clrscr();
    while (allapot > -1) {

        if (allapot == 0) { //fömenü
            econio_gotoxy(0,0);
            std::cout << "Menü\n\n";

            {   //A fömenü kiírása
            if (current == 0)
                if (kcurrent == -1)
                    if (lenyit[0]) {
                        jelenlegi("v Logikák:\n");
                        logiklistaz(logikak, elemszam[0], kcurrent, true);
                    }
                    else
                        jelenlegi("> Logikák:\n");
                else
                    if (lenyit[0]) {
                        std::cout << "v Logikák:\n";
                        logiklistaz(logikak, elemszam[0], kcurrent, true);
                    }
                    else
                        std::cout << "> Logikák:\n";
            else
                if (lenyit[0]) {
                    std::cout << "v Logikák:\n";
                    logiklistaz(logikak, elemszam[0], -1, true);
                }
                else
                    std::cout << "> Logikák:\n";

            if (current == 1)
                if (kcurrent == -1)
                    if (lenyit[1]) {
                        jelenlegi("v Érzékelök:\n");
                        erzlistaz(erzekelok, elemszam[1], kcurrent, true);
                    }
                    else
                        jelenlegi("> Érzékelök:\n");
                else
                    if (lenyit[1]) {
                        std::cout << "v Érzékelök:\n";
                        erzlistaz(erzekelok, elemszam[1], kcurrent, true);
                    }
                    else
                        std::cout << "> Érzékelök:\n";
            else
                if (lenyit[1]) {
                    std::cout << "v Érzékelök:\n";
                    erzlistaz(erzekelok, elemszam[1], -1, true);
                }
                else
                    std::cout << "> Érzékelök:\n";

            if (current == 2)
                if (kcurrent == -1)
                    if (lenyit[2]) {
                        jelenlegi("v Típusok:\n");
                        tiplistaz(tipusok, elemszam[2], kcurrent, true);
                    }
                    else
                        jelenlegi("> Típusok:\n");
                else
                    if (lenyit[2]) {
                        std::cout << "v Típusok:\n";
                        tiplistaz(tipusok, elemszam[2], kcurrent, true);
                    }
                    else
                        std::cout << "> Típusok:\n";
            else
                if (lenyit[2]) {
                    std::cout << "v Típusok:\n";
                    tiplistaz(tipusok, elemszam[2], -1, true);
                }
                else
                    std::cout << "> Típusok:\n";


            if (current == 3)
                if (kcurrent == -1)
                    if (lenyit[3]) {
                        jelenlegi("v Szirénák:\n");
                        szirenlistaz(szirenak, elemszam[3], kcurrent, true);
                    }
                    else
                        jelenlegi("> Szirénák:\n");
                else
                    if (lenyit[3]) {
                        std::cout << "v Szirénák:\n";
                        szirenlistaz(szirenak, elemszam[3], kcurrent, true);
                    }
                    else
                        std::cout << "> Szirénák:\n";
            else
                if (lenyit[3]) {
                    std::cout << "v Szirénák:\n";
                    szirenlistaz(szirenak, elemszam[3], -1, true);
                }
                else
                    std::cout << "> Szirénák:\n";

            if (current == 4)
                if (kcurrent == -1)
                    if (lenyit[4]) {
                        jelenlegi("v Olvasók:\n");
                        olvlistaz(kodolvasok, elemszam[4], kcurrent, true);
                    }
                    else
                        jelenlegi("> Olvasók:\n");
                else
                    if (lenyit[4]) {
                        std::cout << "v Olvasók:\n";
                        olvlistaz(kodolvasok, elemszam[4], kcurrent, true);
                    }
                    else
                        std::cout << "> Olvasók:\n";
            else
                if (lenyit[4]) {
                    std::cout << "v Olvasók:\n";
                    olvlistaz(kodolvasok, elemszam[4], -1, true);
                }
                else
                    std::cout << "> Olvasók:\n";


            if (current == 5)
                jelenlegi("Mentés file-ba\n");
            else
                std::cout << "Mentés file-ba\n";

            if (current == 6)
                jelenlegi("Betöltés file-ból\n");
            else
                std::cout << "Betöltés file-ból\n";


            if (current == 7)
                jelenlegi("Szimuláció\n");
            else
                std::cout << "Szimuláció\n";


            if (current == 8)
                jelenlegi("Kilépés\n");
            else
                std::cout << "Kilépés\n";

            }

            int get = getcharwoent();

            if (lenyit[current]) { //Jelenlegi le van nyitva, akkor léptet
                    if (get == 72 || get == 'w') {
                        if (kcurrent > -1)
                            kcurrent--;
                        else
                        if (kcurrent == -1) {
                            current--;
                            if (lenyit[current])
                                kcurrent = elemszam[current];
                            else
                                kcurrent = -1;
                        }
                    }
                    if (get == 's' || get == 80) {
                        if (kcurrent < elemszam[current] + 1) {
                            kcurrent++;
                        }
                        if (kcurrent == elemszam[current] + 1) {
                            kcurrent = -1;
                            current++;
                        }
                    }
            }
            else { //Ha nincs lenyitva akkor léptet
                if ((get == 72 || get == 'w') && current > 0) {
                    if (lenyit[current - 1])
                        kcurrent = elemszam[current - 1];
                    current--;
                }
                if ((get == 's' || get == 80) && current < 8) {
                    current++;
                }
            }

            if (get == 13) //Enter megnyomásakor
                switch (current) { //Melyik menüpont van kiválasztva
                    case 0:
                        if (kcurrent == -1) {   //Ha a fejléc aktív le fel nyitja
                            lenyit[0] = !lenyit[0];
                            econio_clrscr();
                        }
                        else {  //Egyébként módosít állapotba küld
                            allapot = 4;
                            econio_clrscr();
                            current = 0;
                            if (kcurrent == elemszam[0]) {
                                Logika alap;
                                templ = alap;
                            }
                            else
                                templ = logikak[kcurrent];
                        }
                        break;
                    case 1:
                        if (kcurrent == -1) {
                            lenyit[1] = !lenyit[1];
                            econio_clrscr();
                        }
                        else {
                            allapot = 5;
                            econio_clrscr();
                            current = 0;
                            if (kcurrent == elemszam[1]) {
                                Erzekelo alap;
                                tempe = alap;
                            }
                            else
                                tempe = erzekelok[kcurrent];
                        }
                        break;
                    case 2:
                        if (kcurrent == -1) {
                            lenyit[2] = !lenyit[2];
                            econio_clrscr();
                        }
                        else {
                            allapot = 6;
                            econio_clrscr();
                            current = 0;
                            if (kcurrent == elemszam[2]) {
                                ErzTipus alap;
                                tempt = alap;
                            }
                            else
                                tempt = tipusok[kcurrent];
                        }
                        break;
                    case 3:
                        if (kcurrent == -1) {
                            lenyit[3] = !lenyit[3];
                            econio_clrscr();
                        }
                        else {
                            allapot = 7;
                            econio_clrscr();
                            current = 0;
                            if (kcurrent == elemszam[3]) {
                                Szirena alap;
                                temps = alap;
                            }
                            else
                                temps = szirenak[kcurrent];
                        }
                        break;
                    case 4:
                        if (kcurrent == -1) {
                            lenyit[4] = !lenyit[4];
                            econio_clrscr();
                        }
                        else {
                            allapot = 8;
                            econio_clrscr();
                            current = 0;
                            if (kcurrent == elemszam[4]) {
                                Kodolvaso alap;
                                tempo = alap;
                            }
                            else
                                tempo = kodolvasok[kcurrent];
                        }
                        break;
                    case 5 :
                        allapot = 2;
                        filenev = String();
                        econio_clrscr();
                        break;
                    case 6 :
                        allapot = 3;
                        filenev = String();
                        econio_clrscr();
                        break;
                    case 7 :
                        allapot = 1;
                        current = 0;
                        econio_clrscr();
                        stpmegy = false;
                        ido = 0;
                        break;
                    case 8 :
                        allapot = -1;
                        break;
                }
            if (get == 8 || get == 'b')
                allapot = -1;
        }

        if (allapot == 1) { //szimuláció
            econio_gotoxy(0,0);
            std::cout << "Szimuláció\nEltelt idö:" << ido << "\n\n";

            if (current == 0)
                jelenlegi("> Érzékelök:\n");
            else
                std::cout << "> Érzékelök:\n";

            if (current == 1)
                jelenlegi("> Kódolvasók:\n");
            else
                std::cout << "> Kódolvasók:\n";

            if (current == 2)
                jelenlegi("Kilépés\n");
            else
                std::cout << "Kilépés\n";

            if (stpmegy)
                ido++;

            if (lenyomtae()) {

                int get = getcharwoent();

                if ((get == 72 || get == 'w') && current > 0)
                    current--;
                if ((get == 's' || get == 80) && current < 2)
                    current++;
                if (get == ' ')
                    stpmegy = !stpmegy;
                if (get == 8 || (current == 2 && get == 13) || get == 'b') {
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                }
            }
        }

        if (allapot == 2) { //mentés


            econio_gotoxy(0,0);
            std::cout << "Mentés file-ba\n\nFile név: (vagy elérési út) " << filenev << "\n";
            int get = getcharwoent();
            if (get < 255 && get > 31 && get != 46)
                filenev += get;
            switch (get) {
                case 13 : {//Mentés filenévvel
                    if (mentes(filenev, logikak, erzekelok, tipusok, szirenak, kodolvasok, elemszam))
                        std::cout << "Sikeres mentés!\n";
                    else
                        std::cout << "Mentés sikertelen!\n";
                    std::cout << "Kilépéshez nyomj entert vagy backspace-t.";
                    bool kilep = false;
                    while (!kilep) {
                        get = getcharwoent();
                        if (get == 13 || get == 8)
                            kilep = true;
                    }
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
                }
                case 46 : //Pont nyomása
                    filenev--;
                    econio_clrscr();
                    break;
                case 8 : //Visszagomb
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
            }
        }

        if (allapot == 3) { //betöltés


            econio_gotoxy(0,0);
            std::cout << "Betöltés file-ból\n\nFile név (vagy elérési út):" << filenev << "\n";
            int get = getcharwoent();
            if (get < 255 && get > 31 && get != 46)
                filenev += get;
            switch (get) {
                case 13 : {//Betöltés filenévvel
                    if (betoltes(filenev, &logikak, &erzekelok, &tipusok, &szirenak, &kodolvasok, elemszam))
                        std::cout << "Sikeres betöltés!\n";
                    else
                        std::cout << "Betöltés sikertelen!\n";
                    std::cout << "Kilépéshez nyomj entert vagy backspace-t.";
                    bool kilep = false;
                    while (!kilep) {
                        get = getcharwoent();
                        if (get == 13 || get == 8)
                            kilep = true;
                    }
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
                }
                case 46 :   //Pont megnyomásakor
                    filenev--;
                    econio_clrscr();
                    break;
                case 8 :    //Viosszagomb megnyomásakor
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
            }
        }

        if (allapot == 4) { //Logika szerkesztése
            String alapnev;
            Logika alap;
            bool lelem = false;
            if (kcurrent == elemszam[0])
                alapnev = alap.getnev();
            else
                alapnev = logikak[kcurrent].getnev();

             //Menü kiírása

            std::cout << "Logika szerkesztése\nNév:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("Név: ");
                jelenlegi(templ.getnev());
            }
            else
                std::cout << "Név: " << templ.getnev();
            std::cout << "\n";

            std::cout << "Típus: ";
            switch (templ.getltip()) {
                case es:
                    std::cout << "és";
                    break;
                case vagy:
                    std::cout << "vagy";
                    break;
                case nem:
                    std::cout << "nem";
                    break;
                case idozito:
                    std::cout << "idözitö";
                    break;
            }

            std::cout << "\n";

            if (current == 1)
                if (alkcurrent == -1) {
                    jelenlegi("v Típusok:\n");
                    ltiplistaz(alkcurrent);
                }
                else {
                    std::cout << "v Típusok:\n";
                    ltiplistaz(alkcurrent);
                }
            else {
                std::cout << "v Típusok:\n";
                ltiplistaz(-1);
            }

            std::cout << "Érzékelö(k): ";

            for (size_t i = 0; i < templ.size(); i++)
                if (templ.getelem(i)->gettip() == Erzek)
                    std::cout << templ.getelem(i)->getnev() << " ";
            std::cout << "\n";

            if (current == 2)
                if (alkcurrent == -1) {
                    jelenlegi("v Érzékelök:\n");
                    erzlistaz(erzekelok, elemszam[1], alkcurrent, false);
                }
                else {
                    std::cout << "v Érzékelök:\n";
                    erzlistaz(erzekelok, elemszam[1], alkcurrent, false);
                }
            else {
                std::cout << "v Érzékelök:\n";
                erzlistaz(erzekelok, elemszam[1], -1, false);
            }

            std::cout << "Logika(ák): ";

            for (size_t i = 0; i < templ.size(); i++)
                if (templ.getelem(i)->gettip() == Logik)
                    std::cout << templ.getelem(i)->getnev() << " ";

            std::cout << "\n";

            int index = -1;

            for (int i = 0; i < elemszam[0]; i++)
                if (templ.getnev() == logikak[i].getnev())
                    index = i;

            if (index != -1) {
                Logika *temp = new Logika[elemszam[0] - 1];
                int mlen = 0;
                for (int i = 0; i < elemszam[0]; i++)
                    if (i != index) {
                        temp[mlen] = logikak[i];
                        mlen++;
                    }
                if (current == 3)
                    if (alkcurrent == -1) {
                        jelenlegi("v Logikák:\n");
                        logiklistaz(temp, elemszam[0] - 1, alkcurrent, false);
                    }
                    else {
                        std::cout << "v Logikák:\n";
                        logiklistaz(temp, elemszam[0] - 1, alkcurrent, false);
                    }
                else {
                    std::cout << "v Logikák:\n";
                        logiklistaz(temp, elemszam[0] - 1, -1, false);
                }
                delete[] temp;
            }
            else {
                if (current == 3)
                    if (alkcurrent == -1) {
                        jelenlegi("v Logikák:\n");
                        logiklistaz(logikak, elemszam[0], alkcurrent, false);
                    }
                    else {
                        std::cout << "v Logikák:\n";
                        logiklistaz(logikak, elemszam[0], alkcurrent, false);
                    }
                else {
                    std::cout << "v Logikák:\n";
                        logiklistaz(logikak, elemszam[0], -1, false);
                }
            }

            if (current == 4) {
                jelenlegi("Mentés");
            }
            else
                std::cout << "Mentés";
            std::cout << "\n";

            if (current == 5) {
                jelenlegi("Törlés");
            }
            else
                std::cout << "Törlés";
            std::cout << "\n";

            if (current == 6) {
                jelenlegi("Kilépés");
            }
            else
                std::cout << "Kilépés";
            std::cout << "\n";

            int get = getcharwoent();
            String nev = templ.getnev();

            if (ir == true) { //Név szerkesztésekor
                switch (current) {
                    case 0:
                        if (get < 255 && get > 31 && get != 46) {
                            nev += get;
                            econio_clrscr();
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                nev--;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        templ.setnev(nev);
                        break;
                }
            }
            else {

                if (get == 13 && current == 0) {    //név szerkesztése
                    ir = true;
                }

                if (get == 13 && current == 1 && alkcurrent != -1) {    //Típus kiválasztása
                    switch(alkcurrent) {
                        case 0:
                            templ.setltip(es);
                        break;
                        case 1:
                            templ.setltip(vagy);
                        break;
                        case 2:
                            if (templ.size() != 1) {
                                econio_clrscr();
                                std::cout << "Csak 1 elemü lista lehet ilyen típusú!\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                    get = getcharwoent();
                                econio_clrscr();
                            }
                            else
                                templ.setltip(nem);
                        break;
                        case 3:
                            if (templ.size() != 1) {
                                econio_clrscr();
                                std::cout << "Csak 1 elemü lista lehet ilyen típusú!\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                    get = getcharwoent();
                                econio_clrscr();
                            }
                            else
                                templ.setltip(idozito);
                        break;
                    }
                    econio_clrscr();
                }

                if (get == 13 && current == 2 && alkcurrent != -1) {    //Érzékelö hozzáadása vagy elvétele
                    if (templ.getelem(0)->getnev() == "")
                        templ.rep(erzekelok[alkcurrent].clone(), 0);
                    else
                        if (templ.getltip() == es || templ.getltip() == vagy) {  //Ha éses vagy vagyos akkor hozzáadja
                            int idx = -1;
                            for (size_t i = 0; i < templ.size(); i++)
                                if (templ.getelem(i)->getnev() == erzekelok[alkcurrent].getnev() && templ.getelem(i)->gettip() == Erzek)
                                    idx = (int)i;
                            if (idx != -1 && templ.size() != 1)
                                templ.del(idx);
                            else
                                templ.add(erzekelok[alkcurrent].clone());
                        }
                        else    //egyébként kicseréli
                            templ.rep(erzekelok[alkcurrent].clone(), 0);
                    econio_clrscr();
                }

                if (get == 13 && current == 3 && alkcurrent != -1) {    //Logika hozzáadása vagy elvétele
                    if (templ.getelem(0)->getnev() == "")
                        templ.rep(logikak[alkcurrent].clone(), 0);
                    else
                        if (templ.getltip() == es || templ.getltip() == vagy) {  //Ha éses vagy vagyos akkor hozzáadja
                            int idx = -1;
                            for (size_t i = 0; i < templ.size(); i++)
                                if (templ.getelem(i)->getnev() == logikak[alkcurrent].getnev() && templ.getelem(i)->gettip() == Logik)
                                    idx = (int)i;
                            if (idx != -1 && templ.size() != 1)
                                templ.del(idx);
                            else
                                templ.add(logikak[alkcurrent].clone());
                        }
                        else    //egyébként kicseréli
                            templ.rep(logikak[alkcurrent].clone(), 0);
                    econio_clrscr();
                }

                if (get == 13 && current == 4) {
                    if (templ.getnev() == "" || templ.getelem(0)->getnev() == "") { //Nem menthet név nélkül
                        econio_clrscr();
                            std::cout << "A név vagy az elem nem lehet üres!\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else {
                        int vane = -1;
                        for (int i = 0; i < elemszam[0]; i++)
                            if (logikak[i].getnev() == templ.getnev())
                                vane = i;
                        if (vane != -1) {
                            if (templ.getnev() == alapnev){
                                logikak[vane] = templ;
                                econio_clrscr();
                                std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                            else {
                                econio_clrscr();
                                std::cout << "Már van ilyen nevü logika!\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                        }
                        else {
                            elemszam[0]++;
                            Logika *uj = new Logika[elemszam[0]];
                            for (int i = 0; i < elemszam[0] - 1; i++)
                                uj[i] = logikak[i];
                            uj[elemszam[0] - 1] = templ;
                            delete[] logikak;
                            logikak = uj;
                            kcurrent = elemszam[0] - 1;
                            econio_clrscr();
                            std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                            econio_clrscr();
                        }
                    }
                }

                if (get == 13 && current == 5) {
                    if (kcurrent == elemszam[1]) {
                        econio_clrscr();
                        std::cout << "Ezt nem lehet törölni!\n(folytatáshoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //Törlés, ha nincs használva
                    }
                }

                switch (current) { //Típusok között léptet
                    case 1:
                        if (get == 72 || get == 'w') {
                            if (alkcurrent > -1)
                                alkcurrent--;
                            else
                            if (alkcurrent == -1) {
                                current--;
                                alkcurrent = -1;
                            }
                        }
                        if (get == 's' || get == 80) {
                            if (alkcurrent < 4) {
                                alkcurrent++;
                            }
                            if (alkcurrent == 4) {
                                alkcurrent = -1;
                                current++;
                            }
                        }
                        break;
                    case 2: //Érzékelök között lépked
                        if (get == 72 || get == 'w') {
                            if (alkcurrent > -1)
                                alkcurrent--;
                            else
                            if (alkcurrent == -1) {
                                current--;
                                alkcurrent = 3;
                            }
                        }
                        if (get == 's' || get == 80) {
                            if (alkcurrent < elemszam[1]) {
                                alkcurrent++;
                            }
                            if (alkcurrent == elemszam[1]) {
                                alkcurrent = -1;
                                current++;
                            }
                        }
                        break;
                    case 3: //Logikák között lépked
                        if (get == 72 || get == 'w') {
                            if (alkcurrent > -1) {
                                alkcurrent--;
                                if (alkcurrent == index && index != -1)
                                    alkcurrent--;
                            }
                            else
                            if (alkcurrent == -1) {
                                current--;
                                alkcurrent = elemszam[1] - 1;
                            }
                        }
                        if (get == 's' || get == 80) {
                            if (alkcurrent < elemszam[0] - lelem) {
                                alkcurrent++;
                                if (alkcurrent == index)
                                    alkcurrent++;
                            }
                            if (alkcurrent == elemszam[0] - lelem) {
                                alkcurrent = -1;
                                current++;
                            }
                        }
                        break;
                    default: //Egyébként léptet
                        if ((get == 72 || get == 'w') && current > 0) {
                            if (current == 4) {
                                alkcurrent = elemszam[0] - 1;
                                if (index == elemszam[0] - 1 && index != -1)
                                    alkcurrent--;
                            }
                            current--;
                        }
                        if ((get == 's' || get == 80) && current < 6) {
                            current++;
                        }
                    break;
                }

                if (get == 8 || (current == 6 && get == 13) || get == 'b') {
                    allapot = 0;
                    current = 0;
                    kcurrent = -1;
                    econio_clrscr();
                }
            }

            econio_gotoxy(0,0);
        }

        if (allapot == 5) { //Érzékelö szerkesztése
            String alapnev;
            Erzekelo alap;
            if (kcurrent == elemszam[1])
                alapnev = alap.getnev();
            else
                alapnev = erzekelok[kcurrent].getnev();

            {   //Menü kiírása

            std::cout << "Érzékelö szerkesztése\nNév:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("Név: ");
                jelenlegi(tempe.getnev());
            }
            else
                std::cout << "Név: " << tempe.getnev();
            std::cout << "\n";

            std::cout << "Típus: " << tempe.geterztip().getnev() << "\n";

            if (current == 1)
                if (alkcurrent == -1) {
                    jelenlegi("v Típusok:\n");
                    tiplistaz(tipusok, elemszam[2], alkcurrent, false);
                }
                else {
                    std::cout << "v Típusok:\n";
                    tiplistaz(tipusok, elemszam[2], alkcurrent, false);
                }
            else {
                std::cout << "v Típusok:\n";
                tiplistaz(tipusok, elemszam[2], -1, false);
            }

            if (current == 2) {
                jelenlegi("Mentés");
            }
            else
                std::cout << "Mentés";
            std::cout << "\n";

            if (current == 3) {
                jelenlegi("Törlés");
            }
            else
                std::cout << "Törlés";
            std::cout << "\n";

            if (current == 4) {
                jelenlegi("Kilépés");
            }
            else
                std::cout << "Kilépés";
            std::cout << "\n";

            }

            int get = getcharwoent();
            String nev = tempe.getnev();

            if (ir == true) { //Elem szerkesztésekor
                switch (current) {
                    case 0:
                        if (get < 255 && get > 31 && get != 46) {
                            nev += get;
                            econio_clrscr();
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                nev--;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        tempe.setnev(nev);
                        break;
                }
            }
            else {

                if (get == 13 && current == 2) {
                    if (tempe.getnev() == "" || tempe.geterztip().getnev() == "") { //Nem menthet név nélkül
                        econio_clrscr();
                            std::cout << "A név vagy a típus nem lehet üres!\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else {
                        int vane = -1;
                        for (int i = 0; i < elemszam[1]; i++)
                            if (erzekelok[i].getnev() == tempe.getnev())
                                vane = i;
                        if (vane != -1) {
                            if (tempe.getnev() == alapnev){
                                erzekelok[vane] = tempe;
                                econio_clrscr();
                                    std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                                    get = getcharwoent();
                                    while(get != 13)
                                    get = getcharwoent();
                                econio_clrscr();
                            }
                            else {
                                econio_clrscr();
                                    std::cout << "Már van ilyen nevü érzékelö!\n(folytatáshoz nyomj entert)";
                                    get = getcharwoent();
                                    while(get != 13)
                                    get = getcharwoent();
                                econio_clrscr();
                            }
                        }
                        else {
                            elemszam[1]++;
                            Erzekelo *uj = new Erzekelo[elemszam[1]];
                            for (size_t i = 0; (int)i < elemszam[1] - 1; i++)
                                uj[i] = erzekelok[i];
                            uj[elemszam[1] - 1] = tempe;
                            delete[] erzekelok;
                            erzekelok = uj;
                            econio_clrscr();
                                std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                            econio_clrscr();
                        }
                    }
                }

                if (get == 13 && current == 3) {
                    if (kcurrent == elemszam[1]) {
                        econio_clrscr();
                        std::cout << "Ezt nem lehet törölni!\n(folytatáshoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //Törlés, ha nincs használva
                    }
                }

                if (get == 13 && current == 0) {
                    ir = true;
                }

                if (get == 13 && current == 1 && alkcurrent != -1) {
                    tempe.seterztip(tipusok[alkcurrent]);
                }

                if (current == 1) { //Típusok között léptet
                    if (get == 72 || get == 'w') {
                        if (alkcurrent > -1)
                            alkcurrent--;
                        else
                        if (alkcurrent == -1) {
                            current--;
                            alkcurrent = -1;
                        }
                    }
                    if (get == 's' || get == 80) {
                        if (alkcurrent < elemszam[2]) {
                            alkcurrent++;
                        }
                        if (alkcurrent == elemszam[2]) {
                            alkcurrent = -1;
                            current++;
                        }
                    }
                }
                else { //Egyébként léptet
                    if ((get == 72 || get == 'w') && current > 0) {
                        if (current == 2)
                            alkcurrent = elemszam[2] - 1;
                        current--;
                    }
                    if ((get == 's' || get == 80) && current < 4) {
                        current++;
                    }
                }

                if (get == 8 || (current == 4 && get == 13) || get == 'b') {
                    allapot = 0;
                    current = 0;
                    kcurrent = -1;
                    econio_clrscr();
                }
            }

            econio_gotoxy(0,0);
        }

        if (allapot == 6) { //Típus szerkesztése

            String alapnev;
            ErzTipus alap;
            if (kcurrent == elemszam[2])
                alapnev = alap.getnev();
            else
                alapnev = tipusok[kcurrent].getnev();

            {   //Menü kiírása

            std::cout << "Típus szerkesztése\nNév:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("Név: ");
                jelenlegi(tempt.getnev());
            }
            else
                std::cout << "Név: " << tempt.nev.c_str();
            std::cout << "\n";

            if (current == 1) {
                jelenlegi("Alap: ");
                jelenlegi(tempt.getalap());
            }
            else
                std::cout << "Alap: " << tempt.getalap();
            std::cout << "\n";

            if (current == 2) {
                jelenlegi("Alsó: ");
                jelenlegi(tempt.getalso());
            }
            else
                std::cout << "Alsó: " << tempt.getalso();
            std::cout << "\n";

            if (current == 3) {
                jelenlegi("Felsö: ");
                jelenlegi(tempt.getfelso());
            }
            else
                std::cout << "Felsö: " << tempt.getfelso();
            std::cout << "\n";

            if (current == 4) {
                jelenlegi("Mentés");
            }
            else
                std::cout << "Mentés";
            std::cout << "\n";

            if (current == 5) {
                jelenlegi("Törlés");
            }
            else
                std::cout << "Törlés";
            std::cout << "\n";

            if (current == 6) {
                jelenlegi("Kilépés");
            }
            else
                std::cout << "Kilépés";
            std::cout << "\n";

            }

            int get = getcharwoent();
            String nev = tempt.getnev();

            if (ir == true) { //Elem szerkesztésekor
                switch (current) {
                    case 0:
                        if (get < 255 && get > 31 && get != 46) {
                            nev += get;
                            econio_clrscr();
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                nev--;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        tempt.setnev(nev);
                        break;
                    case 1:
                        {
                        int uj = tempt.getalap();
                        if (get >= '0' && get <= '9') {
                            if (uj >= 0)
                                uj = 10 * uj + get - '0';
                            else
                                uj = 10 * uj - get + '0';
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                uj = uj / 10;
                                econio_clrscr();
                                break;
                            case 45 :
                                uj = - uj;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        tempt.setalap(uj);
                        break;
                        }
                    case 2:
                        {
                        int uj = tempt.getalso();
                        if (get >= '0' && get <= '9') {
                            if (uj >= 0)
                                uj = 10 * uj + get - '0';
                            else
                                uj = 10 * uj - get + '0';
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                uj = uj / 10;
                                econio_clrscr();
                                break;
                            case 45 :
                                uj = - uj;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        tempt.setalso(uj);
                        break;
                        }
                    case 3:
                        {
                        int uj = tempt.getfelso();
                        if (get >= '0' && get <= '9') {
                            if (uj >= 0)
                                uj = 10 * uj + get - '0';
                            else
                                uj = 10 * uj - get + '0';
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                uj = uj / 10;
                                econio_clrscr();
                                break;
                            case 45 :
                                uj = - uj;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        tempt.setfelso(uj);
                        break;
                        }
                }
            }
            else {

                if (get == 13 && current == 4) {
                    if (tempt.getnev() == "") { //Nem menthet név nélkül
                        econio_clrscr();
                        std::cout << "A név nem lehet üres!\n(folytatáshoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                        get = getcharwoent();
                        econio_clrscr();
                    }
                    else {
                        int vane = -1;
                        for (int i = 0; i < elemszam[2]; i++)   //Megnézzük, hogy van-e névütközés
                            if (tipusok[i].getnev() == tempt.getnev())
                                vane = i;
                        if (vane != -1) {
                            if (tempt.getnev() == alapnev){ //Ha van, de ezt nyitottuk meg, akkor felülírjuk
                                tipusok[vane] = tempt;
                                for (int i = 0; i < elemszam[1]; i++)
                                    if (erzekelok[i].geterztip().getnev() == tempt.getnev())
                                        erzekelok[i].seterztip(tempt);
                                econio_clrscr();
                                std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                            else {  //Egyébként nem menthet
                                econio_clrscr();
                                std::cout << "Már van ilyen nevü típus!\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                        }
                        else {  //Ha nincs elmentjük
                            elemszam[2]++;
                            ErzTipus *uj = new ErzTipus[elemszam[2]];
                            for (size_t i = 0; (int)i < elemszam[2] - 1; i++)
                                uj[i] = tipusok[i];
                            uj[elemszam[2] - 1] = tempt;
                            delete[] tipusok;
                            tipusok = uj;
                            kcurrent = elemszam[2] - 1;
                            econio_clrscr();
                            std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                            econio_clrscr();
                        }
                    }
                }

                if (get == 13 && current == 5) {
                    if (kcurrent == elemszam[2]) {
                        econio_clrscr();
                        std::cout << "Ezt nem lehet törölni!\n(folytatáshoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //Törlés, ha nincs használva és létezik ilyen nevü
                        int idx = -1;
                        for (int i = 0; i < elemszam[2]; i++)
                            if (tipusok[i].getnev() == tempt.getnev())
                                idx = i;
                        if (idx == -1) {
                            econio_clrscr();
                            std::cout << "Nincs ilyen nevü típus!\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                                get = getcharwoent();
                            econio_clrscr();
                        }
                        else {
                            bool vane = false;
                            for (int i = 0; i < elemszam[1]; i++)
                                if (erzekelok[i].geterztip().getnev() == tempt.getnev())
                                    vane = true;
                            if (vane) {
                                econio_clrscr();
                                std::cout << "Ez a típus használatban van! Csak nem használtat lehet törölni.\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                    get = getcharwoent();
                                econio_clrscr();
                            }
                            else {
                                elemszam[2]--;
                                ErzTipus* temp = new ErzTipus[elemszam[2]];
                                int mlen = 0;
                                for (int i = 0; i < elemszam[2] + 1; i++) {
                                    if (i != idx) {
                                        temp[mlen] = tipusok[i];
                                        mlen++;
                                    }
                                }
                                delete[] tipusok;
                                tipusok = temp;
                                econio_clrscr();
                                std::cout << "Sikeres törlés.\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                    get = getcharwoent();
                                econio_clrscr();
                            }
                        }
                    }
                }

                if (get == 13 && current != 5 && current != 4 && current != 6) {
                    ir = true;
                }

                if ((get == 72 || get == 'w') && current > 0) {
                    current--;
                }

                if ((get == 's' || get == 80) && current < 6) {
                    current++;
                }

                if (get == 8 || (current == 6 && get == 13) || get == 'b') {
                    allapot = 0;
                    current = 0;
                    kcurrent = -1;
                    econio_clrscr();
                }
            }

            econio_gotoxy(0,0);
        }

        if (allapot == 7) { //Sziréna szerkesztése
            String alapnev;
            Szirena alap;
            if (kcurrent == elemszam[3])
                alapnev = alap.getnev();
            else
                alapnev = szirenak[kcurrent].getnev();

            {   //Menü kiírása

            std::cout << "Érzékelö szerkesztése\nNév:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("Név: ");
                jelenlegi(temps.getnev());
            }
            else
                std::cout << "Név: " << temps.getnev();
            std::cout << "\n";

            if (current == 1) {
                jelenlegi("Idözités: ");
                jelenlegi(temps.getidoz());
            }
            else
                std::cout << "Idözités: " << temps.getidoz();
            std::cout << "\n";

            std::cout << "Logika: ";
            if (temps.getlogika() != 0) std::cout << temps.getlogika()->getnev();
            std::cout << "\n";

            if (current == 2)
                if (alkcurrent == -1) {
                    jelenlegi("v Logikák:\n");
                    logiklistaz(logikak, elemszam[0], alkcurrent, false);
                }
                else {
                    std::cout << "v Logikák:\n";
                    logiklistaz(logikak, elemszam[0], alkcurrent, false);
                }
            else {
                std::cout << "v Logikák:\n";
                logiklistaz(logikak, elemszam[0], -1, false);
            }

            std::cout << "Olvasó: ";
            if (temps.getolvas() != 0) std::cout << temps.getolvas()->getnev();
            std::cout << "\n";

            if (current == 3)
                if (alkcurrent == -1) {
                    jelenlegi("v Olvasók:\n");
                    olvlistaz(kodolvasok, elemszam[4], alkcurrent, false);
                }
                else {
                    std::cout << "v Olvasók:\n";
                    olvlistaz(kodolvasok, elemszam[4], alkcurrent, false);
                }
            else {
                std::cout << "v Olvasók:\n";
                olvlistaz(kodolvasok, elemszam[4], -1, false);
            }

            if (current == 4) {
                jelenlegi("Mentés");
            }
            else
                std::cout << "Mentés";
            std::cout << "\n";

            if (current == 5) {
                jelenlegi("Törlés");
            }
            else
                std::cout << "Törlés";
            std::cout << "\n";

            if (current == 6) {
                jelenlegi("Kilépés");
            }
            else
                std::cout << "Kilépés";
            std::cout << "\n";

            }

            int get = getcharwoent();
            String nev = temps.getnev();

            if (ir == true) { //Elem szerkesztésekor
                switch (current) {
                    case 0:
                        if (get < 255 && get > 31 && get != 46) {
                            nev += get;
                            econio_clrscr();
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                nev--;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        temps.setnev(nev);
                        break;
                    case 1:
                        {
                        int uj = temps.getidoz();
                        if (get >= '0' && get <= '9') {
                            if (uj >= 0)
                                uj = 10 * uj + get - '0';
                            else
                                uj = 10 * uj - get + '0';
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                uj = uj / 10;
                                econio_clrscr();
                                break;
                            case 45 :
                                uj = - uj;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        temps.setidoz(uj);
                        break;
                        }
                }
            }
            else {

                if (get == 13 && (current == 0 || current == 1)) {
                    ir = true;
                }

                if (get == 13 && current == 2 && alkcurrent != -1) {
                    temps.setlogika(&logikak[alkcurrent]);
                }

                if (get == 13 && current == 3 && alkcurrent != -1) {
                    temps.setolvas(&kodolvasok[alkcurrent]);
                }

                if (get == 13 && current == 4) {    //Mentés
                    if (temps.getnev() == "" || temps.getlogika() == 0 || temps.getolvas() == 0) { //Nem menthet név nélkül
                        econio_clrscr();
                            std::cout << "A név, a logika, vagy az olvasó nem lehet üres!\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else {
                        int vane = -1;
                        for (int i = 0; i < elemszam[3]; i++)
                            if (szirenak[i].getnev() == temps.getnev())
                                vane = i;
                        if (vane != -1) {
                            if (temps.getnev() == alapnev){
                                szirenak[vane] = temps;
                                econio_clrscr();
                                std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                            else {
                                econio_clrscr();
                                std::cout << "Már van ilyen nevü érzékelö!\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                        }
                        else {
                            elemszam[3]++;
                            Szirena *uj = new Szirena[elemszam[3]];
                            for (size_t i = 0; (int)i < elemszam[3] - 1; i++)
                                uj[i] = szirenak[i];
                            uj[elemszam[3] - 1] = temps;
                            delete[] szirenak;
                            szirenak = uj;
                            econio_clrscr();
                            std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                            econio_clrscr();
                        }
                    }
                }

                if (get == 13 && current == 5) {    //Törlés
                    if (kcurrent == elemszam[3]) {
                        econio_clrscr();
                        std::cout << "Ezt nem lehet törölni!\n(folytatáshoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else {  //Törlés, mert úgysincs használva
                        elemszam[3]--;
                        Szirena* temp = new Szirena[elemszam[3]];
                        int mlen = 0;
                        for (int i = 0; i < elemszam[3] + 1; i++) {
                            if (szirenak[i].getnev() != temps.getnev()) {
                                temp[mlen] = szirenak[i];
                                mlen++;
                            }
                        }
                        delete[] szirenak;
                        szirenak = temp;
                        econio_clrscr();
                        std::cout << "Sikeres törlés.\n(folytatáshoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                }

                if (get == 8 || (current == 6 && get == 13) || get == 'b') { //kilépés
                    allapot = 0;
                    current = 0;
                    kcurrent = -1;
                    econio_clrscr();
                }


                switch (current) {
                    case 2: //Logikák között lépked
                        if (get == 72 || get == 'w') {
                            if (alkcurrent > -1) {
                                alkcurrent--;
                            }
                            else
                            if (alkcurrent == -1) {
                                current--;
                                alkcurrent = - 1;
                            }
                        }
                        if (get == 's' || get == 80) {
                            if (alkcurrent < elemszam[0]) {
                                alkcurrent++;
                            }
                            if (alkcurrent == elemszam[0]) {
                                alkcurrent = -1;
                                current++;
                            }
                        }
                        break;
                    case 3: //Olvasók között lépked
                        if (get == 72 || get == 'w') {
                            if (alkcurrent > -1)
                                alkcurrent--;
                            else
                            if (alkcurrent == -1) {
                                current--;
                                alkcurrent = elemszam[0] - 1;
                            }
                        }
                        if (get == 's' || get == 80) {
                            if (alkcurrent < elemszam[4]) {
                                alkcurrent++;
                            }
                            if (alkcurrent == elemszam[4]) {
                                alkcurrent = -1;
                                current++;
                            }
                        }
                        break;
                    default: //Egyébként léptet
                        if ((get == 72 || get == 'w') && current > 0) {
                            if (current == 4) {
                                alkcurrent = elemszam[4] - 1;
                            }
                            current--;
                        }
                        if ((get == 's' || get == 80) && current < 6) {
                            current++;
                        }
                    break;
                }

            }

            econio_gotoxy(0,0);
        }

        if (allapot == 8) { //Olvasó szerkesztése

            String alapnev;
            Kodolvaso alap;
            if (kcurrent == elemszam[4])
                alapnev = alap.getnev();
            else
                alapnev = kodolvasok[kcurrent].getnev();

            {   //Menü kiírása

            std::cout << "Olvasó szerkesztése\nEredeti név:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("Név: ");
                jelenlegi(tempo.getnev());
            }
            else
                std::cout << "Név: " << tempo.getnev().c_str();
            std::cout << "\n";

            if (current == 1) {
                jelenlegi("Érték: ");
                jelenlegi(tempo.getert());
            }
            else
                std::cout << "Érték: " << tempo.getert();
            std::cout << "\n";

            if (current == 2) {
                jelenlegi("Mentés");
            }
            else
                std::cout << "Mentés";
            std::cout << "\n";

            if (current == 3) {
                jelenlegi("Törlés");
            }
            else
                std::cout << "Törlés";
            std::cout << "\n";

            if (current == 4) {
                jelenlegi("Kilépés");
            }
            else
                std::cout << "Kilépés";
            std::cout << "\n";

            }

            int get = getcharwoent();
            String nev = tempo.getnev();

            if (ir == true) { //Elem szerkesztésekor
                switch (current) {
                    case 0:
                        if (get < 255 && get > 31 && get != 46) {
                            nev += get;
                            econio_clrscr();
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                nev--;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        tempo.setnev(nev);
                        break;
                    case 1:
                        {
                        int uj = tempo.getert();
                        if (get >= '0' && get <= '9') {
                            if (uj >= 0)
                                uj = 10 * uj + get - '0';
                            else
                                uj = 10 * uj - get + '0';
                        }
                        switch (get) {
                            case 13 :
                                ir = false;
                                break;
                            case 46 :
                                uj = uj / 10;
                                econio_clrscr();
                                break;
                            case 45 :
                                uj = - uj;
                                econio_clrscr();
                                break;
                            case 8 :
                                ir = false;
                                break;
                        }
                        tempo.setert(uj);
                        break;
                        }
                }
            }
            else {

                if (get == 13 && current == 2) {
                    if (tempo.getnev() == "") { //Nem menthet név nélkül
                        econio_clrscr();
                            std::cout << "A név nem lehet üres!\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else {
                        int vane = -1;
                        for (int i = 0; i < elemszam[4]; i++)
                            if (kodolvasok[i].getnev() == tempo.getnev())
                                vane = i;
                        if (vane != -1) { // ha van ütközés
                            if (tempo.getnev() == alapnev){ // ha a jelenlegi az akkor menthetjük, egyébként nem
                                kodolvasok[vane] = tempo;
                                for (int i = 0; i < elemszam[3]; i++)
                                    if (szirenak[i].getolvas()->getnev() == tempo.getnev())
                                        szirenak[i].setolvas(&tempo);
                                econio_clrscr();
                                std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                            else {
                                econio_clrscr();
                                std::cout << "Már van ilyen nevü olvasó!\n(folytatáshoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                        }
                        else {
                            elemszam[4]++;
                            Kodolvaso *uj = new Kodolvaso[elemszam[4]];
                            for (size_t i = 0; (int)i < elemszam[4] - 1; i++)
                                uj[i] = kodolvasok[i];
                            uj[elemszam[4] - 1] = tempo;
                            delete[] kodolvasok;
                            kodolvasok = uj;
                            econio_clrscr();
                            std::cout << "Mentés kész\n(folytatáshoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                            econio_clrscr();
                        }
                    }
                }

                if (get == 13 && current == 3) {
                    if (kcurrent == elemszam[4]) {
                        econio_clrscr();
                        std::cout << "Ezt nem lehet törölni!\n(folytatáshoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //Törlés, ha nincs használva

                    }
                }

                if (get == 13 && current != 2 && current != 3 && current != 4) {
                    ir = true;
                }

                if ((get == 72 || get == 'w') && current > 0) {
                    current--;
                }

                if ((get == 's' || get == 80) && current < 4) {
                    current++;
                }

                if (get == 8 || (current == 4 && get == 13) || get == 'b') {
                    allapot = 0;
                    current = 0;
                    kcurrent = -1;
                    econio_clrscr();
                }
            }

            econio_gotoxy(0,0);
        }
    }

    if (logikak != nullptr)
        delete[] logikak;
    if (erzekelok != nullptr)
        delete[] erzekelok;
    if (tipusok != nullptr)
        delete[] tipusok;
    if (szirenak != nullptr)
        delete[] szirenak;
    if (kodolvasok != nullptr)
        delete[] kodolvasok;


}
