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
            jelenlegi("> Logikák:\n");
        else
            std::cout << "> Logikák:\n";


        if (current == 1)
            jelenlegi("> Érzékelõk:\n");
        else
            std::cout << "> Érzékelõk:\n";


        if (current == 2)
            jelenlegi("> Kódolvasók:\n");
        else
            std::cout << "> Kódolvasók:\n";


        if (current == 3)
            jelenlegi("Mentés file-ba\n");
        else
            std::cout << "Mentés file-ba\n";

        if (current == 4)
            jelenlegi("Betõltés file-ból\n");
        else
            std::cout << "Betõltés file-ból\n";


        if (current == 5)
            jelenlegi("Szimuláció\n");
        else
            std::cout << "Szimuláció\n";


        if (current == 6)
            jelenlegi("Kilépés\n");
        else
            std::cout << "Kilépés\n";


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
