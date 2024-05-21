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

void jelenlegi(const String& be) { //Kiemeli a bej�v� sztringet
    econio_textbackground(COL_WHITE);
    econio_textcolor(COL_BLACK);
    std::cout << be;
    econio_textbackground(COL_BLACK);
    econio_textcolor(COL_WHITE);
}

void logiklistaz(Logika* elemek, size_t darab, int kcurrent) { //Kilist�zza a logik�kat a konzolra
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
        jelenlegi("  �j Logika\n");
    else
        std::cout << "  �j Logika\n";
}

void erzlistaz(Erzekelo* elemek, size_t darab, int kcurrent) { //Kilist�zza a �rz�kel�ket a konzolra
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
        jelenlegi("  �j �rz�kel�\n");
    else
        std::cout << "  �j �rz�kel�\n";
}

void tiplistaz(ErzTipus* elemek, size_t darab, int kcurrent) { //Kilist�zza a t�pusokat a konzolra
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
        jelenlegi("  �j T�pus\n");
    else
        std::cout << "  �j T�pus\n";
}

void szirenlistaz(Szirena* elemek, size_t darab, int kcurrent) { //Kilist�zza a szir�n�kat a konzolra
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
        jelenlegi("  �j Szir�na\n");
    else
        std::cout << "  �j Szir�na\n";
}

void olvlistaz(Kodolvaso* elemek, size_t darab, int kcurrent) { //Kilist�zza az olvas�kat a konzolra
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
        jelenlegi("  �j Olvas�\n");
    else
        std::cout << "  �j Olvas�\n";
}


int main() {

    #ifdef _WIN32
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif

    std::cout << "Oszt�lyok tesztel�se:\n\n";

    test_all();

    std::cout << "Tesztek befejezve.\nKil�p�shez vissza gomb, folytat�shoz enter.\n";

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
    bool ir = false;

    Logika templ;
    Erzekelo tempe;
    ErzTipus tempt;
    Szirena  temps;
    Kodolvaso tempo;



    econio_clrscr();
    while (allapot > -1) {
        if (allapot == 0) { //f�men�
            econio_gotoxy(0,0);
            std::cout << "Alap/\n\n";

            {   //A f�men� ki�r�sa
            if (current == 0)
                if (kcurrent == -1)
                    if (lenyit[0]) {
                        jelenlegi("v Logik�k:\n");
                        logiklistaz(logikak, elemszam[0], kcurrent);
                    }
                    else
                        jelenlegi("> Logik�k:\n");
                else
                    if (lenyit[0]) {
                        std::cout << "v Logik�k:\n";
                        logiklistaz(logikak, elemszam[0], kcurrent);
                    }
                    else
                        std::cout << "> Logik�k:\n";
            else
                if (lenyit[0]) {
                    std::cout << "v Logik�k:\n";
                    logiklistaz(logikak, elemszam[0], -1);
                }
                else
                    std::cout << "> Logik�k:\n";

            if (current == 1)
                if (kcurrent == -1)
                    if (lenyit[1]) {
                        jelenlegi("v �rz�kel�k:\n");
                        erzlistaz(erzekelok, elemszam[1], kcurrent);
                    }
                    else
                        jelenlegi("> �rz�kel�k:\n");
                else
                    if (lenyit[1]) {
                        std::cout << "v �rz�kel�k:\n";
                        erzlistaz(erzekelok, elemszam[1], kcurrent);
                    }
                    else
                        std::cout << "> �rz�kel�k:\n";
            else
                if (lenyit[1]) {
                    std::cout << "v �rz�kel�k:\n";
                    erzlistaz(erzekelok, elemszam[1], -1);
                }
                else
                    std::cout << "> �rz�kel�k:\n";

            if (current == 2)
                if (kcurrent == -1)
                    if (lenyit[2]) {
                        jelenlegi("v T�pusok:\n");
                        tiplistaz(tipusok, elemszam[2], kcurrent);
                    }
                    else
                        jelenlegi("> T�pusok:\n");
                else
                    if (lenyit[2]) {
                        std::cout << "v T�pusok:\n";
                        tiplistaz(tipusok, elemszam[2], kcurrent);
                    }
                    else
                        std::cout << "> T�pusok:\n";
            else
                if (lenyit[2]) {
                    std::cout << "v T�pusok:\n";
                    tiplistaz(tipusok, elemszam[2], -1);
                }
                else
                    std::cout << "> T�pusok:\n";


            if (current == 3)
                if (kcurrent == -1)
                    if (lenyit[3]) {
                        jelenlegi("v Szir�n�k:\n");
                        szirenlistaz(szirenak, elemszam[3], kcurrent);
                    }
                    else
                        jelenlegi("> Szir�n�k:\n");
                else
                    if (lenyit[3]) {
                        std::cout << "v Szir�n�k:\n";
                        szirenlistaz(szirenak, elemszam[3], kcurrent);
                    }
                    else
                        std::cout << "> Szir�n�k:\n";
            else
                if (lenyit[3]) {
                    std::cout << "v Szir�n�k:\n";
                    szirenlistaz(szirenak, elemszam[3], -1);
                }
                else
                    std::cout << "> Szir�n�k:\n";

            if (current == 4)
                if (kcurrent == -1)
                    if (lenyit[4]) {
                        jelenlegi("v Olvas�k:\n");
                        olvlistaz(kodolvasok, elemszam[4], kcurrent);
                    }
                    else
                        jelenlegi("> Olvas�k:\n");
                else
                    if (lenyit[4]) {
                        std::cout << "v Olvas�k:\n";
                        olvlistaz(kodolvasok, elemszam[4], kcurrent);
                    }
                    else
                        std::cout << "> Olvas�k:\n";
            else
                if (lenyit[4]) {
                    std::cout << "v Olvas�k:\n";
                    olvlistaz(kodolvasok, elemszam[4], -1);
                }
                else
                    std::cout << "> Olvas�k:\n";


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

            }

            int get = getcharwoent();

            if (lenyit[current]) { //Jelenlegi le van nyitva, akkor l�ptet
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
            else { //Ha nincs lenyitva akkor l�ptet
                if ((get == 72 || get == 'w') && current > 0) {
                    if (lenyit[current - 1])
                        kcurrent = elemszam[current - 1];
                    current--;
                }
                if ((get == 's' || get == 80) && current < 8) {
                    current++;
                }
            }

            if (get == 13) //Enter megnyom�sakor
                switch (current) { //Melyik men�pont van kiv�lasztva
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

        if (allapot == 2) { //ment�s


            econio_gotoxy(0,0);
            std::cout << "Ment�s file-ba\n\nFile n�v: (vagy el�r�si �t)" << filenev << "\n";
            int get = getcharwoent();
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
                        get = getcharwoent();
                        if (get == 13 || get == 8)
                            kilep = true;
                    }
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
                }
                case 46 : //Pont nyom�sa
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
        if (allapot == 3) { //bet�lt�s


            econio_gotoxy(0,0);
            std::cout << "Bet�lt�s file-b�l\n\nFile n�v (vagy el�r�si �t):" << filenev << "\n";
            int get = getcharwoent();
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
                        get = getcharwoent();
                        if (get == 13 || get == 8)
                            kilep = true;
                    }
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
                }
                case 46 :   //Pont megnyom�sakor
                    filenev--;
                    econio_clrscr();
                    break;
                case 8 :    //Viosszagomb megnyom�sakor
                    allapot = 0;
                    current = 0;
                    econio_clrscr();
                    break;
            }
        }
        if (allapot == 4) { //Logika szerkeszt�se

            /*

            std::cout << "Logika szerkeszt�se\n\n";
            std::cout << "T�pus:\n";

            if (temp.getltip() == es)
                jelenlegi("�s\n");
            else
                std::cout << "�s\n";

            econio_gotoxy(0,0);*/
        }

        if (allapot == 5) { //�rz�kel� szerkeszt�se

        }

        if (allapot == 6) { //T�pus szerkeszt�se

            String alapnev;
            ErzTipus alap;
            if (kcurrent == elemszam[2])
                alapnev = alap.getnev();
            else
                alapnev = tipusok[kcurrent].getnev();

            {   //Men� ki�r�sa

            std::cout << "T�pus szerkeszt�se\nEredeti n�v:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("N�v: ");
                jelenlegi(tempt.getnev());
            }
            else
                std::cout << "N�v: " << tempt.nev.c_str();
            std::cout << "\n";

            if (current == 1) {
                jelenlegi("Alap: ");
                jelenlegi(tempt.getalap());
            }
            else
                std::cout << "Alap: " << tempt.getalap();
            std::cout << "\n";

            if (current == 2) {
                jelenlegi("Als�: ");
                jelenlegi(tempt.getalso());
            }
            else
                std::cout << "Als�: " << tempt.getalso();
            std::cout << "\n";

            if (current == 3) {
                jelenlegi("Fels�: ");
                jelenlegi(tempt.getfelso());
            }
            else
                std::cout << "Fels�: " << tempt.getfelso();
            std::cout << "\n";

            if (current == 4) {
                jelenlegi("Ment�s");
            }
            else
                std::cout << "Ment�s";
            std::cout << "\n";

            if (current == 5) {
                jelenlegi("T�rl�s");
            }
            else
                std::cout << "T�rl�s";
            std::cout << "\n";

            if (current == 6) {
                jelenlegi("Kil�p�s");
            }
            else
                std::cout << "Kil�p�s";
            std::cout << "\n";

            }

            int get = getcharwoent();
            String nev = tempt.getnev();

            if (ir == true) { //Elem szerkeszt�sekor
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
                    int vane = -1;
                    for (int i = 0; i < elemszam[2]; i++)
                        if (tipusok[i].getnev() == tempt.getnev())
                            vane = i;
                    if (vane != -1) {
                        if (tempt.getnev() == alapnev){
                            tipusok[vane] = tempt;
                            econio_clrscr();
                                std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                            econio_clrscr();
                        }
                        else {
                            econio_clrscr();
                                std::cout << "M�r van ilyen nev� t�pus!\n(folytat�shoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                            econio_clrscr();
                        }
                    }
                    else {
                        elemszam[2]++;
                        ErzTipus *uj = new ErzTipus[elemszam[2]];
                        for (size_t i = 0; (int)i < elemszam[2] - 1; i++)
                            uj[i] = tipusok[i];
                        uj[elemszam[2] - 1] = tempt;
                        delete[] tipusok;
                        tipusok = uj;
                        econio_clrscr();
                            std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                }

                if (get == 13 && current == 5) {
                    if (kcurrent == elemszam[2]) {
                        econio_clrscr();
                        std::cout << "Ezt nem lehet t�r�lni!\n(folytat�shoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //T�rl�s, ha nincs haszn�lva

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

        if (allapot == 7) { //Szir�na szerkeszt�se

        }

        if (allapot == 8) { //Olvas� szerkeszt�se

            String alapnev;
            Kodolvaso alap;
            if (kcurrent == elemszam[4])
                alapnev = alap.getnev();
            else
                alapnev = kodolvasok[kcurrent].getnev();

            {   //Men� ki�r�sa

            std::cout << "Olvas� szerkeszt�se\nEredeti n�v:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("N�v: ");
                jelenlegi(tempo.getnev());
            }
            else
                std::cout << "N�v: " << tempo.getnev().c_str();
            std::cout << "\n";

            if (current == 1) {
                jelenlegi("�rt�k: ");
                jelenlegi(tempo.getert());
            }
            else
                std::cout << "�rt�k: " << tempo.getert();
            std::cout << "\n";

            if (current == 2) {
                jelenlegi("Ment�s");
            }
            else
                std::cout << "Ment�s";
            std::cout << "\n";

            if (current == 3) {
                jelenlegi("T�rl�s");
            }
            else
                std::cout << "T�rl�s";
            std::cout << "\n";

            if (current == 4) {
                jelenlegi("Kil�p�s");
            }
            else
                std::cout << "Kil�p�s";
            std::cout << "\n";

            }

            int get = getcharwoent();
            String nev = tempo.getnev();

            if (ir == true) { //Elem szerkeszt�sekor
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
                    int vane = -1;
                    for (int i = 0; i < elemszam[4]; i++)
                        if (kodolvasok[i].getnev() == tempo.getnev())
                            vane = i;
                    if (vane != -1) {
                        if (tempo.getnev() == alapnev){
                            kodolvasok[vane] = tempo;
                            econio_clrscr();
                                std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                            econio_clrscr();
                        }
                        else {
                            econio_clrscr();
                                std::cout << "M�r van ilyen nev� olvas�!\n(folytat�shoz nyomj entert)";
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
                            std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                }

                if (get == 13 && current == 3) {
                    if (kcurrent == elemszam[4]) {
                        econio_clrscr();
                        std::cout << "Ezt nem lehet t�r�lni!\n(folytat�shoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //T�rl�s, ha nincs haszn�lva

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
