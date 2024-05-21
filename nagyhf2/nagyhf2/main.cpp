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


bool mentes(String &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Szirena* szirenak, Kodolvaso* kodolvasok, int *elemszam) {

    std::ofstream f;
    f.open(filenev.c_str());
    if (!f)
        return false;
    for (size_t i = 0; i < 5; i++)
            f << elemszam[i] << ' ';
    f << '\n';
    for (int i = 0; i < elemszam[2]; i++) {
        f << tipusok[i].getnev() << ' ' << tipusok[i].getalap() << ' ' << tipusok[i].getalso() << ' ' << tipusok[i].getfelso() << "\n";
    }
    for (int i = 0; i < elemszam[1]; i++) {
        f << erzekelok[i].getnev() << ' ' << erzekelok[i].geterztip().getnev() << "\n";
    }
    for (int i = 0; i < elemszam[0]; i++) {
        f << logikak[i].getnev() << ' ' << logikak[i].gettip() << ' ' << logikak[i].getidoz() << ' ' << logikak[i].size() << "\n";
        for (size_t a = 0; a < logikak[i].size(); a++)
            f << logikak[i].getelem(a)->gettip() << ' ' << logikak[i].getelem(a)->getnev() << "\n";
    }
    for (int i = 0; i < elemszam[4]; i++) {
        f << kodolvasok[i].getnev() << ' ' << kodolvasok[i].getert() << "\n";
    }
    for (int i = 0; i < elemszam[3]; i++) {
        f << szirenak[i].getnev() << ' ' << szirenak[i].getlogika()->getnev() << ' ' << szirenak[i].getidoz() << ' ' << szirenak[i].getolvas()->getnev() << "\n";
    }
    f.close();

    return true;
}

bool betoltes(String &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Kodolvaso* kodolvasok) {return true;}

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


int main() {

    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif

    std::cout << "Osztályok tesztelése:\n\n";

    test_all();

    std::cout << "Tesztek befejezve.\nKilépéshez vissza gomb, folytatáshoz enter.\n";

    int tveg = getcharwoent();
    while (tveg != 13 && tveg != 8 && tveg != 'b') {
        tveg = getcharwoent();
    }
    int allapot;
    tveg == 13 ? allapot = 0 : allapot = -1;


    struct timespec tstart={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    int current = 0, ido = 0, kcurrent = -1, alkcurrent = -1, elemszam[5] = {0};
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
                        if (kcurrent == -1) {
                            lenyit[0] = !lenyit[0];
                            econio_clrscr();
                        }
                        /*else {
                            allapot = 4;
                            econio_clrscr();
                        }*/
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
                    if (betoltes(filenev, logikak, erzekelok, tipusok, kodolvasok))
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
                        if (vane != -1) {
                            if (tempo.getnev() == alapnev){
                                kodolvasok[vane] = tempo;
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
    if (kodolvasok != nullptr)
        delete[] kodolvasok;


}
