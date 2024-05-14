#include <iostream>
#include <time.h>
#include <conio.h>
#include "c-econio/econio.h"

#include "Erzekelo.h"
#include "Eszkoz.h"
#include "Szirena.h"
#include "Tipus.h"
#include "Logika.h"
#include "Kodolvaso.h"


#ifdef _WIN32
    #include <windows.h>
#endif

bool mentes(std::string &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Kodolvaso* kodolvasok) {return true;}

bool betoltes(std::string &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Kodolvaso* kodolvasok) {return true;}

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

    struct timespec tstart={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    int current = 0, ido = 0;
    bool stpmegy = false, lenyit[5] = {0};
    std::string filenev("");
    Logika* logikak = 0;
    Erzekelo* erzekelok = 0;
    ErzTipus* tipusok = 0;
    Kodolvaso* kodolvasok = 0;
    for (int allapot = 0; allapot > -1;) {
        if (allapot == 0) { //f�men�
            econio_gotoxy(0,0);
            std::cout << "Alap/\n\n";


            if (current == 0)
                jelenlegi("> Logik�k:\n");
            else
                std::cout << "> Logik�k:\n";


            if (current == 1)
                jelenlegi("> �rz�kel�k:\n");
            else
                std::cout << "> �rz�kel�k:\n";

            if (current == 2)
                jelenlegi("> T�pusok:\n");
            else
                std::cout << "> T�pusok:\n";


            if (current == 3)
                jelenlegi("> Szir�n�k:\n");
            else
                std::cout << "> Szir�n�k:\n";

            if (current == 4)
                jelenlegi("> K�dolvas�k:\n");
            else
                std::cout << "> K�dolvas�k:\n";


            if (current == 5)
                jelenlegi("Ment�s file-ba\n");
            else
                std::cout << "Ment�s file-ba\n";

            if (current == 6)
                jelenlegi("Bet�lt�s file-b�l\n");
            else
                std::cout << "Bet�lt�s file-b�l\n";


            if (current == 7)
                jelenlegi("Szimul�ci�\n");
            else
                std::cout << "Szimul�ci�\n";


            if (current == 8)
                jelenlegi("Kil�p�s\n");
            else
                std::cout << "Kil�p�s\n";



            int get = getch();
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
        if (allapot == 1) { //szimul�ci�
            econio_gotoxy(0,0);
            std::cout << "Szimul�ci�\nEltelt id�:" << ido << "\n\n";

            if (current == 0)
                jelenlegi("> �rz�kel�k:\n");
            else
                std::cout << "> �rz�kel�k:\n";

            if (current == 1)
                jelenlegi("> K�dolvas�k:\n");
            else
                std::cout << "> K�dolvas�k:\n";

            if (current == 2)
                jelenlegi("Kil�p�s\n");
            else
                std::cout << "Kil�p�s\n";

            if (stpmegy)
                ido++;

            if (kbhit()) {

                int get = getch();

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
        if (allapot == 2) { //ment�s
            econio_gotoxy(0,0);
            std::cout << "Ment�s file-ba\n\nFile n�v: (vagy el�r�si �t)" << filenev << "\n";
            int get = getch();
            if (get < 255 && get > 31 && get != 46)
                filenev += get;
            switch (get) {
                case 13 : {//Ment�s filen�vvel
                    if (mentes(filenev, logikak, erzekelok, tipusok, kodolvasok))
                        std::cout << "Sikeres ment�s!\n";
                    else
                        std::cout << "Ment�s sikertelen!\n";
                    std::cout << "Kil�p�shez nyomj entert vagy backspace-t.";
                    bool kilep = false;
                    while (!kilep) {
                        get = getch();
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
        if (allapot == 3) { //bet�lt�s
            econio_gotoxy(0,0);
            std::cout << "Bet�lt�s file-b�l\n\nFile n�v (vagy el�r�si �t):" << filenev << "\n";
            int get = getch();
            if (get < 255 && get > 31 && get != 46)
                filenev += get;
            switch (get) {
                case 13 : {//Bet�lt�s filen�vvel
                    if (betoltes(filenev, logikak, erzekelok, tipusok, kodolvasok))
                        std::cout << "Sikeres bet�lt�s!\n";
                    else
                        std::cout << "Bet�lt�s sikertelen!\n";
                    std::cout << "Kil�p�shez nyomj entert vagy backspace-t.";
                    bool kilep = false;
                    while (!kilep) {
                        get = getch();
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
