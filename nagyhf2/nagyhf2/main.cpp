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


bool mentes(std::string &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Kodolvaso* kodolvasok) {return true;}

bool betoltes(std::string &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Kodolvaso* kodolvasok) {return true;}

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

void jelenlegi(const char* be) {
    econio_textbackground(COL_WHITE);
    econio_textcolor(COL_BLACK);
    std::cout << be;
    econio_textbackground(COL_BLACK);
    econio_textcolor(COL_WHITE);
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
    int current = 0, ido = 0;
    bool stpmegy = false, lenyit[5] = {0};
    std::string filenev("");
    Logika* logikak = 0;
    Erzekelo* erzekelok = 0;
    ErzTipus* tipusok = 0;
    Kodolvaso* kodolvasok = 0;
    econio_clrscr();
    while (allapot > -1) {
        if (allapot == 0) { //fömenü
            econio_gotoxy(0,0);
            std::cout << "Alap/\n\n";


            if (current == 0)
                jelenlegi("> Logikák:\n");
            else
                std::cout << "> Logikák:\n";


            if (current == 1)
                jelenlegi("> Érzékelök:\n");
            else
                std::cout << "> Érzékelök:\n";

            if (current == 2)
                jelenlegi("> Típusok:\n");
            else
                std::cout << "> Típusok:\n";


            if (current == 3)
                jelenlegi("> Szirénák:\n");
            else
                std::cout << "> Szirénák:\n";

            if (current == 4)
                jelenlegi("> Kódolvasók:\n");
            else
                std::cout << "> Kódolvasók:\n";


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
            if ((get == 72 || get == 'w') && current > 0)
                current--;
            if ((get == 's' || get == 80) && current < 8)
                current++;
            if (get == 13)
                switch (current) {
                    case 0 || 1 || 2 || 3 || 4:
                        lenyit[current] = ! lenyit[current];
                        break;
                    case 5 :
                        allapot = 2;
                        filenev.erase();
                        econio_clrscr();
                        break;
                    case 6 :
                        allapot = 3;
                        filenev.erase();
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
                    filenev.pop_back();
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
                    filenev.pop_back();
                    econio_clrscr();
                    break;
                case 8 :
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
            }
        }
    }

}
