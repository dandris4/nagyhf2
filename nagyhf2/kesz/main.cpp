#include <iostream>
#include <time.h>
#include "econio.h"

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


bool mentes(String &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Kodolvaso* kodolvasok) {

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

void jelenlegi(const String& be) {
    econio_textbackground(COL_WHITE);
    econio_textcolor(COL_BLACK);
    std::cout << be;
    econio_textbackground(COL_BLACK);
    econio_textcolor(COL_WHITE);
}

void logiklistaz(Logika* elemek, size_t darab, int kcurrent) {
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if ((size_t)kcurrent == darab)
        jelenlegi("  Új Logika\n");
    else
        std::cout << "  Új Logika\n";
}

void erzlistaz(Erzekelo* elemek, size_t darab, int kcurrent) {
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if ((size_t)kcurrent == darab)
        jelenlegi("  Új Érzékelö\n");
    else
        std::cout << "  Új Érzékelö\n";
}

void tiplistaz(ErzTipus* elemek, size_t darab, int kcurrent) {
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if ((size_t)kcurrent == darab)
        jelenlegi("  Új Típus\n");
    else
        std::cout << "  Új Típus\n";
}

void szirenlistaz(Szirena* elemek, size_t darab, int kcurrent) {
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if ((size_t)kcurrent == darab)
        jelenlegi("  Új Sziréna\n");
    else
        std::cout << "  Új Sziréna\n";
}

void olvlistaz(Kodolvaso* elemek, size_t darab, int kcurrent) {
    for (size_t i = 0; i < darab; i++) {
        String kiir = "  ";
        kiir += elemek[i].getnev();
        kiir += '\n';
        if (i == (size_t)kcurrent)
            jelenlegi(kiir);
        else
            std::cout << kiir;
    }
    if ((size_t)kcurrent == darab)
        jelenlegi("  Új Olvasó\n");
    else
        std::cout << "  Új Olvasó\n";
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
    int current = 0, ido = 0, kcurrent = -1, elemszam[5] = {0};
    bool stpmegy = false, lenyit[5] = {0};
    String filenev("");
    Logika* logikak = nullptr;
    Erzekelo* erzekelok = nullptr;
    ErzTipus* tipusok = nullptr;
    Szirena* szirenak = nullptr;
    Kodolvaso* kodolvasok = nullptr;

    ErzTipus alapt("alap",0,0,0);
    Erzekelo alape("alap",alapt);
    Logika alapl("alap",es,alape.clone());
    Kodolvaso alapo("alap");
    Szirena alapsz("alap", &alapl, 0, &alapo);

    econio_clrscr();
    while (allapot > -1) {
        if (allapot == 0) { //fömenü
            econio_gotoxy(0,0);
            std::cout << "Alap/\n\n";


            if (current == 0)
                if (kcurrent == -1)
                    if (lenyit[0]) {
                        jelenlegi("v Logikák:\n");
                        logiklistaz(logikak, elemszam[0], kcurrent);
                    }
                    else
                        jelenlegi("> Logikák:\n");
                else
                    if (lenyit[0]) {
                        std::cout << "v Logikák:\n";
                        logiklistaz(logikak, elemszam[0], kcurrent);
                    }
                    else
                        std::cout << "> Logikák:\n";
            else
                if (lenyit[0]) {
                    std::cout << "v Logikák:\n";
                    logiklistaz(logikak, elemszam[0], -1);
                }
                else
                    std::cout << "> Logikák:\n";

            if (current == 1)
                if (kcurrent == -1)
                    if (lenyit[1]) {
                        jelenlegi("v Érzékelök:\n");
                        erzlistaz(erzekelok, elemszam[1], kcurrent);
                    }
                    else
                        jelenlegi("> Érzékelök:\n");
                else
                    if (lenyit[1]) {
                        std::cout << "v Érzékelök:\n";
                        erzlistaz(erzekelok, elemszam[1], kcurrent);
                    }
                    else
                        std::cout << "> Érzékelök:\n";
            else
                if (lenyit[1]) {
                    std::cout << "v Érzékelök:\n";
                    erzlistaz(erzekelok, elemszam[1], -1);
                }
                else
                    std::cout << "> Érzékelök:\n";

            if (current == 2)
                if (kcurrent == -1)
                    if (lenyit[2]) {
                        jelenlegi("v Típusok:\n");
                        tiplistaz(tipusok, elemszam[2], kcurrent);
                    }
                    else
                        jelenlegi("> Típusok:\n");
                else
                    if (lenyit[2]) {
                        std::cout << "v Típusok:\n";
                        tiplistaz(tipusok, elemszam[2], kcurrent);
                    }
                    else
                        std::cout << "> Típusok:\n";
            else
                if (lenyit[2]) {
                    std::cout << "v Típusok:\n";
                    tiplistaz(tipusok, elemszam[2], -1);
                }
                else
                    std::cout << "> Típusok:\n";


            if (current == 3)
                if (kcurrent == -1)
                    if (lenyit[3]) {
                        jelenlegi("v Szirénák:\n");
                        szirenlistaz(szirenak, elemszam[3], kcurrent);
                    }
                    else
                        jelenlegi("> Szirénák:\n");
                else
                    if (lenyit[3]) {
                        std::cout << "v Szirénák:\n";
                        szirenlistaz(szirenak, elemszam[3], kcurrent);
                    }
                    else
                        std::cout << "> Szirénák:\n";
            else
                if (lenyit[3]) {
                    std::cout << "v Szirénák:\n";
                    szirenlistaz(szirenak, elemszam[3], -1);
                }
                else
                    std::cout << "> Szirénák:\n";

            if (current == 4)
                if (kcurrent == -1)
                    if (lenyit[4]) {
                        jelenlegi("v Olvasók:\n");
                        olvlistaz(kodolvasok, elemszam[4], kcurrent);
                    }
                    else
                        jelenlegi("> Olvasók:\n");
                else
                    if (lenyit[4]) {
                        std::cout << "v Olvasók:\n";
                        olvlistaz(kodolvasok, elemszam[4], kcurrent);
                    }
                    else
                        std::cout << "> Olvasók:\n";
            else
                if (lenyit[4]) {
                    std::cout << "v Olvasók:\n";
                    olvlistaz(kodolvasok, elemszam[4], -1);
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



            int get = getcharwoent();
            if (lenyit[current]) {
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
            else {
                if ((get == 72 || get == 'w') && current > 0) {
                    if (lenyit[current - 1])
                        kcurrent = elemszam[current - 1];
                    current--;
                }
                if ((get == 's' || get == 80) && current < 8) {
                    current++;
                }
            }

            if (get == 13)
                switch (current) {
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
                        break;
                    case 2:
                        if (kcurrent == -1) {
                            lenyit[2] = !lenyit[2];
                            econio_clrscr();
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
            std::cout << "Mentés file-ba\n\nFile név: (vagy elérési út)" << filenev << "\n";
            int get = getcharwoent();
            if (get < 255 && get > 31 && get != 46)
                filenev += get;
            switch (get) {
                case 13 : {//Mentés filenévvel
                    if (mentes(filenev, logikak, erzekelok, tipusok, kodolvasok))
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
                case 46 :
                    filenev--;
                    econio_clrscr();
                    break;
                case 8 :
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
                case 46 :
                    filenev--;
                    econio_clrscr();
                    break;
                case 8 :
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
            }
        }
        if (allapot == 4) {
            Logika temp(alapl);

            std::cout << "Logika szerkesztése\n\n";
            std::cout << "Típus:\n";

            if (temp.getltip() == es)
                jelenlegi("És\n");
            else
                std::cout << "És\n";

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
