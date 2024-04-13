#include <iostream>
#include <time.h>
#include <conio.h>
#include "c-econio/econio.h"
#ifdef _WIN32
    #include <windows.h>
#endif

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
    int current = 0;
    for (int i = 0; i < 1;) {
        econio_clrscr();
        std::cout << "Alap\n\n";


        if (current == 0)
            jelenlegi("> Logik�k:\n");
        else
            std::cout << "> Logik�k:\n";


        if (current == 1)
            jelenlegi("> �rz�kel�k:\n");
        else
            std::cout << "> �rz�kel�k:\n";


        if (current == 2)
            jelenlegi("> K�dolvas�k:\n");
        else
            std::cout << "> K�dolvas�k:\n";


        if (current == 3)
            jelenlegi("Ment�s file-ba\n");
        else
            std::cout << "Ment�s file-ba\n";

        if (current == 4)
            jelenlegi("Bet�lt�s file-b�l\n");
        else
            std::cout << "Bet�lt�s file-b�l\n";


        if (current == 5)
            jelenlegi("Szimul�ci�\n");
        else
            std::cout << "Szimul�ci�\n";


        if (current == 6)
            jelenlegi("Kil�p�s\n");
        else
            std::cout << "Kil�p�s\n";


        int get = getch();
        if ((get == 72 || get == 'w') && current > 0)
            current--;
        if ((get == 's' || get == 80) && current < 6)
            current++;
        if (get == 8 || (current == 6 && get == 13))
            i = 1;
        std::cout << (int)'\n';
    }

}
