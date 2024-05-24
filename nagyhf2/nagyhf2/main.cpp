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


bool mentes(String &filenev, Logika* logikak, Erzekelo* erzekelok, ErzTipus* tipusok, Szirena* szirenak, Kodolvaso* kodolvasok, int *elemszam) { //Ha siker�lt megnyitni a file-t bele�rja az elemeket

    std::ofstream f;
    f.open(filenev.c_str());
    if (!f)
        return false;
    for (size_t i = 0; i < 5; i++)
            f << elemszam[i] << ' ';
    f << '\n';
    for (int i = 0; i < elemszam[2]; i++) { //�rz�kel� t�pusok be�r�sa
        f << tipusok[i].getnev() << ' ' << tipusok[i].getalap() << ' ' << tipusok[i].getalso() << ' ' << tipusok[i].getfelso() << "\n";
    }
    for (int i = 0; i < elemszam[1]; i++) { //�rz�kel�k be�r�sa
        f << erzekelok[i].getnev() << ' ' << erzekelok[i].geterztip().getnev() << "\n";
    }
    for (int i = 0; i < elemszam[0]; i++) { //Logik�k be�r�sa
        f << logikak[i].getnev() << ' ' << logikak[i].getltip() << ' ' << logikak[i].getidoz() << ' ' << logikak[i].size() << "\n";
        for (size_t a = 0; a < logikak[i].size(); a++)
            f << logikak[i].getelem(a)->gettip() << ' ' << logikak[i].getelem(a)->getnev() << "\n";
    }
    for (int i = 0; i < elemszam[4]; i++) { //K�dolvas�k be�r�sa
        f << kodolvasok[i].getnev() << ' ' << kodolvasok[i].getert() << "\n";
    }
    for (int i = 0; i < elemszam[3]; i++) { //Szir�n�k be�r�sa
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

    for (int i = 0; i < telemszam[2]; i++) { //�rz�kel� t�pusok olvas�sa
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

    for (int i = 0; i < telemszam[1]; i++) { //�rz�kel�k olvas�sa
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

    for (int i = 0; i < telemszam[0]; i++) { //Logik�k olvas�sa
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

        for (int a = 0; a < len; a++) { //Elemeinek olvas�sa
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

    for (int i = 0; i < telemszam[4]; i++) { //K�dolvas�k olvas�sa
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

    for (int i = 0; i < telemszam[3]; i++) { //Szir�n�k olvas�sa
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

void jelenlegi(const String& be) { //Kiemeli a bej�v� sztringet
    econio_textbackground(COL_WHITE);
    econio_textcolor(COL_BLACK);
    std::cout << be;
    econio_textbackground(COL_BLACK);
    econio_textcolor(COL_WHITE);
}

void logiklistaz(Logika* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilist�zza a logik�kat a konzolra
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
            jelenlegi("  �j Logika\n");
        else
            std::cout << "  �j Logika\n";
    }
}

void erzlistaz(Erzekelo* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilist�zza a �rz�kel�ket a konzolra
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
            jelenlegi("  �j �rz�kel�\n");
        else
            std::cout << "  �j �rz�kel�\n";
    }
}

void tiplistaz(ErzTipus* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilist�zza a t�pusokat a konzolra
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
            jelenlegi("  �j T�pus\n");
        else
            std::cout << "  �j T�pus\n";
    }
}

void szirenlistaz(Szirena* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilist�zza a szir�n�kat a konzolra
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
            jelenlegi("  �j Szir�na\n");
        else
            std::cout << "  �j Szir�na\n";
    }
}

void olvlistaz(Kodolvaso* elemek, size_t darab, int kcurrent, bool ujkiir) { //Kilist�zza az olvas�kat a konzolra
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
            jelenlegi("  �j Olvas�\n");
        else
            std::cout << "  �j Olvas�\n";
    }
}

void ltiplistaz(int kcurrent) { //Kilist�zza a logika t�pusokat a konzolra
    char lis[][8 + 1] = {"�s\n", "vagy\n", "nem\n", "id�zit�\n"};
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

    std::cout << "Oszt�lyok tesztel�se:\n\n";

    test_all();// A tester.cpp �sszes tesztj�t lefuttatja

    std::cout << "Tesztek befejezve.\nKil�p�shez vissza gomb, folytat�shoz enter.\n";

    int tveg = getcharwoent();
    while (tveg != 13 && tveg != 8 && tveg != 'b') { //Enterre folytatja, visszagombra vagy b-re kil�p
        tveg = getcharwoent();
    }
    int allapot;
    tveg == 13 ? allapot = 0 : allapot = -1;

    int current = 0, //A jelenlegi poz�ci�t mutat
    ido = 0,         //A szimul�ci�ban mutatja az eltelt id�t
    kcurrent = -1,   //A lenyitott �llapotban mutatja, hogy melyik elem van kijel�lve
    alkcurrent = -1,    //Egy elem szerkeszt�sekor mutatja, hogy melyik elem van kijel�lve
    elemszam[5] = {0};  //Megmondja, hogy milyen t�pus� elemb�l mennyi van (Logika, �rz�kel�, t�pus, szir�na, k�dolvas�)
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
            std::cout << "Men�\n\n";

            {   //A f�men� ki�r�sa
            if (current == 0)
                if (kcurrent == -1)
                    if (lenyit[0]) {
                        jelenlegi("v Logik�k:\n");
                        logiklistaz(logikak, elemszam[0], kcurrent, true);
                    }
                    else
                        jelenlegi("> Logik�k:\n");
                else
                    if (lenyit[0]) {
                        std::cout << "v Logik�k:\n";
                        logiklistaz(logikak, elemszam[0], kcurrent, true);
                    }
                    else
                        std::cout << "> Logik�k:\n";
            else
                if (lenyit[0]) {
                    std::cout << "v Logik�k:\n";
                    logiklistaz(logikak, elemszam[0], -1, true);
                }
                else
                    std::cout << "> Logik�k:\n";

            if (current == 1)
                if (kcurrent == -1)
                    if (lenyit[1]) {
                        jelenlegi("v �rz�kel�k:\n");
                        erzlistaz(erzekelok, elemszam[1], kcurrent, true);
                    }
                    else
                        jelenlegi("> �rz�kel�k:\n");
                else
                    if (lenyit[1]) {
                        std::cout << "v �rz�kel�k:\n";
                        erzlistaz(erzekelok, elemszam[1], kcurrent, true);
                    }
                    else
                        std::cout << "> �rz�kel�k:\n";
            else
                if (lenyit[1]) {
                    std::cout << "v �rz�kel�k:\n";
                    erzlistaz(erzekelok, elemszam[1], -1, true);
                }
                else
                    std::cout << "> �rz�kel�k:\n";

            if (current == 2)
                if (kcurrent == -1)
                    if (lenyit[2]) {
                        jelenlegi("v T�pusok:\n");
                        tiplistaz(tipusok, elemszam[2], kcurrent, true);
                    }
                    else
                        jelenlegi("> T�pusok:\n");
                else
                    if (lenyit[2]) {
                        std::cout << "v T�pusok:\n";
                        tiplistaz(tipusok, elemszam[2], kcurrent, true);
                    }
                    else
                        std::cout << "> T�pusok:\n";
            else
                if (lenyit[2]) {
                    std::cout << "v T�pusok:\n";
                    tiplistaz(tipusok, elemszam[2], -1, true);
                }
                else
                    std::cout << "> T�pusok:\n";


            if (current == 3)
                if (kcurrent == -1)
                    if (lenyit[3]) {
                        jelenlegi("v Szir�n�k:\n");
                        szirenlistaz(szirenak, elemszam[3], kcurrent, true);
                    }
                    else
                        jelenlegi("> Szir�n�k:\n");
                else
                    if (lenyit[3]) {
                        std::cout << "v Szir�n�k:\n";
                        szirenlistaz(szirenak, elemszam[3], kcurrent, true);
                    }
                    else
                        std::cout << "> Szir�n�k:\n";
            else
                if (lenyit[3]) {
                    std::cout << "v Szir�n�k:\n";
                    szirenlistaz(szirenak, elemszam[3], -1, true);
                }
                else
                    std::cout << "> Szir�n�k:\n";

            if (current == 4)
                if (kcurrent == -1)
                    if (lenyit[4]) {
                        jelenlegi("v Olvas�k:\n");
                        olvlistaz(kodolvasok, elemszam[4], kcurrent, true);
                    }
                    else
                        jelenlegi("> Olvas�k:\n");
                else
                    if (lenyit[4]) {
                        std::cout << "v Olvas�k:\n";
                        olvlistaz(kodolvasok, elemszam[4], kcurrent, true);
                    }
                    else
                        std::cout << "> Olvas�k:\n";
            else
                if (lenyit[4]) {
                    std::cout << "v Olvas�k:\n";
                    olvlistaz(kodolvasok, elemszam[4], -1, true);
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
                        if (kcurrent == -1) {   //Ha a fejl�c akt�v le fel nyitja
                            lenyit[0] = !lenyit[0];
                            econio_clrscr();
                        }
                        else {  //Egy�bk�nt m�dos�t �llapotba k�ld
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
            std::cout << "Ment�s file-ba\n\nFile n�v: (vagy el�r�si �t) " << filenev << "\n";
            int get = getcharwoent();
            if (get < 255 && get > 31 && get != 46)
                filenev += get;
            switch (get) {
                case 13 : {//Ment�s filen�vvel
                    if (mentes(filenev, logikak, erzekelok, tipusok, szirenak, kodolvasok, elemszam))
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
                    if (betoltes(filenev, &logikak, &erzekelok, &tipusok, &szirenak, &kodolvasok, elemszam))
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
            String alapnev;
            Logika alap;
            bool lelem = false;
            if (kcurrent == elemszam[0])
                alapnev = alap.getnev();
            else
                alapnev = logikak[kcurrent].getnev();

             //Men� ki�r�sa

            std::cout << "Logika szerkeszt�se\nN�v:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("N�v: ");
                jelenlegi(templ.getnev());
            }
            else
                std::cout << "N�v: " << templ.getnev();
            std::cout << "\n";

            std::cout << "T�pus: ";
            switch (templ.getltip()) {
                case es:
                    std::cout << "�s";
                    break;
                case vagy:
                    std::cout << "vagy";
                    break;
                case nem:
                    std::cout << "nem";
                    break;
                case idozito:
                    std::cout << "id�zit�";
                    break;
            }

            std::cout << "\n";

            if (current == 1)
                if (alkcurrent == -1) {
                    jelenlegi("v T�pusok:\n");
                    ltiplistaz(alkcurrent);
                }
                else {
                    std::cout << "v T�pusok:\n";
                    ltiplistaz(alkcurrent);
                }
            else {
                std::cout << "v T�pusok:\n";
                ltiplistaz(-1);
            }

            std::cout << "�rz�kel�(k): ";

            for (size_t i = 0; i < templ.size(); i++)
                if (templ.getelem(i)->gettip() == Erzek)
                    std::cout << templ.getelem(i)->getnev() << " ";
            std::cout << "\n";

            if (current == 2)
                if (alkcurrent == -1) {
                    jelenlegi("v �rz�kel�k:\n");
                    erzlistaz(erzekelok, elemszam[1], alkcurrent, false);
                }
                else {
                    std::cout << "v �rz�kel�k:\n";
                    erzlistaz(erzekelok, elemszam[1], alkcurrent, false);
                }
            else {
                std::cout << "v �rz�kel�k:\n";
                erzlistaz(erzekelok, elemszam[1], -1, false);
            }

            std::cout << "Logika(�k): ";

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
                        jelenlegi("v Logik�k:\n");
                        logiklistaz(temp, elemszam[0] - 1, alkcurrent, false);
                    }
                    else {
                        std::cout << "v Logik�k:\n";
                        logiklistaz(temp, elemszam[0] - 1, alkcurrent, false);
                    }
                else {
                    std::cout << "v Logik�k:\n";
                        logiklistaz(temp, elemszam[0] - 1, -1, false);
                }
                delete[] temp;
            }
            else {
                if (current == 3)
                    if (alkcurrent == -1) {
                        jelenlegi("v Logik�k:\n");
                        logiklistaz(logikak, elemszam[0], alkcurrent, false);
                    }
                    else {
                        std::cout << "v Logik�k:\n";
                        logiklistaz(logikak, elemszam[0], alkcurrent, false);
                    }
                else {
                    std::cout << "v Logik�k:\n";
                        logiklistaz(logikak, elemszam[0], -1, false);
                }
            }

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

            int get = getcharwoent();
            String nev = templ.getnev();

            if (ir == true) { //N�v szerkeszt�sekor
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

                if (get == 13 && current == 0) {    //n�v szerkeszt�se
                    ir = true;
                }

                if (get == 13 && current == 1 && alkcurrent != -1) {    //T�pus kiv�laszt�sa
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
                                std::cout << "Csak 1 elem� lista lehet ilyen t�pus�!\n(folytat�shoz nyomj entert)";
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
                                std::cout << "Csak 1 elem� lista lehet ilyen t�pus�!\n(folytat�shoz nyomj entert)";
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

                if (get == 13 && current == 2 && alkcurrent != -1) {    //�rz�kel� hozz�ad�sa vagy elv�tele
                    if (templ.getelem(0)->getnev() == "")
                        templ.rep(erzekelok[alkcurrent].clone(), 0);
                    else
                        if (templ.getltip() == es || templ.getltip() == vagy) {  //Ha �ses vagy vagyos akkor hozz�adja
                            int idx = -1;
                            for (size_t i = 0; i < templ.size(); i++)
                                if (templ.getelem(i)->getnev() == erzekelok[alkcurrent].getnev() && templ.getelem(i)->gettip() == Erzek)
                                    idx = (int)i;
                            if (idx != -1 && templ.size() != 1)
                                templ.del(idx);
                            else
                                templ.add(erzekelok[alkcurrent].clone());
                        }
                        else    //egy�bk�nt kicser�li
                            templ.rep(erzekelok[alkcurrent].clone(), 0);
                    econio_clrscr();
                }

                if (get == 13 && current == 3 && alkcurrent != -1) {    //Logika hozz�ad�sa vagy elv�tele
                    if (templ.getelem(0)->getnev() == "")
                        templ.rep(logikak[alkcurrent].clone(), 0);
                    else
                        if (templ.getltip() == es || templ.getltip() == vagy) {  //Ha �ses vagy vagyos akkor hozz�adja
                            int idx = -1;
                            for (size_t i = 0; i < templ.size(); i++)
                                if (templ.getelem(i)->getnev() == logikak[alkcurrent].getnev() && templ.getelem(i)->gettip() == Logik)
                                    idx = (int)i;
                            if (idx != -1 && templ.size() != 1)
                                templ.del(idx);
                            else
                                templ.add(logikak[alkcurrent].clone());
                        }
                        else    //egy�bk�nt kicser�li
                            templ.rep(logikak[alkcurrent].clone(), 0);
                    econio_clrscr();
                }

                if (get == 13 && current == 4) {
                    if (templ.getnev() == "" || templ.getelem(0)->getnev() == "") { //Nem menthet n�v n�lk�l
                        econio_clrscr();
                            std::cout << "A n�v vagy az elem nem lehet �res!\n(folytat�shoz nyomj entert)";
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
                                std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                            else {
                                econio_clrscr();
                                std::cout << "M�r van ilyen nev� logika!\n(folytat�shoz nyomj entert)";
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
                            std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
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
                        std::cout << "Ezt nem lehet t�r�lni!\n(folytat�shoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //T�rl�s, ha nincs haszn�lva
                    }
                }

                switch (current) { //T�pusok k�z�tt l�ptet
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
                    case 2: //�rz�kel�k k�z�tt l�pked
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
                    case 3: //Logik�k k�z�tt l�pked
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
                    default: //Egy�bk�nt l�ptet
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

        if (allapot == 5) { //�rz�kel� szerkeszt�se
            String alapnev;
            Erzekelo alap;
            if (kcurrent == elemszam[1])
                alapnev = alap.getnev();
            else
                alapnev = erzekelok[kcurrent].getnev();

            {   //Men� ki�r�sa

            std::cout << "�rz�kel� szerkeszt�se\nN�v:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("N�v: ");
                jelenlegi(tempe.getnev());
            }
            else
                std::cout << "N�v: " << tempe.getnev();
            std::cout << "\n";

            std::cout << "T�pus: " << tempe.geterztip().getnev() << "\n";

            if (current == 1)
                if (alkcurrent == -1) {
                    jelenlegi("v T�pusok:\n");
                    tiplistaz(tipusok, elemszam[2], alkcurrent, false);
                }
                else {
                    std::cout << "v T�pusok:\n";
                    tiplistaz(tipusok, elemszam[2], alkcurrent, false);
                }
            else {
                std::cout << "v T�pusok:\n";
                tiplistaz(tipusok, elemszam[2], -1, false);
            }

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
            String nev = tempe.getnev();

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
                        tempe.setnev(nev);
                        break;
                }
            }
            else {

                if (get == 13 && current == 2) {
                    if (tempe.getnev() == "" || tempe.geterztip().getnev() == "") { //Nem menthet n�v n�lk�l
                        econio_clrscr();
                            std::cout << "A n�v vagy a t�pus nem lehet �res!\n(folytat�shoz nyomj entert)";
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
                                    std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                                    get = getcharwoent();
                                    while(get != 13)
                                    get = getcharwoent();
                                econio_clrscr();
                            }
                            else {
                                econio_clrscr();
                                    std::cout << "M�r van ilyen nev� �rz�kel�!\n(folytat�shoz nyomj entert)";
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
                                std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
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
                        std::cout << "Ezt nem lehet t�r�lni!\n(folytat�shoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //T�rl�s, ha nincs haszn�lva
                    }
                }

                if (get == 13 && current == 0) {
                    ir = true;
                }

                if (get == 13 && current == 1 && alkcurrent != -1) {
                    tempe.seterztip(tipusok[alkcurrent]);
                }

                if (current == 1) { //T�pusok k�z�tt l�ptet
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
                else { //Egy�bk�nt l�ptet
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

        if (allapot == 6) { //T�pus szerkeszt�se

            String alapnev;
            ErzTipus alap;
            if (kcurrent == elemszam[2])
                alapnev = alap.getnev();
            else
                alapnev = tipusok[kcurrent].getnev();

            {   //Men� ki�r�sa

            std::cout << "T�pus szerkeszt�se\nN�v:" << alapnev << "\n\n";

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
                    if (tempt.getnev() == "") { //Nem menthet n�v n�lk�l
                        econio_clrscr();
                        std::cout << "A n�v nem lehet �res!\n(folytat�shoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                        get = getcharwoent();
                        econio_clrscr();
                    }
                    else {
                        int vane = -1;
                        for (int i = 0; i < elemszam[2]; i++)   //Megn�zz�k, hogy van-e n�v�tk�z�s
                            if (tipusok[i].getnev() == tempt.getnev())
                                vane = i;
                        if (vane != -1) {
                            if (tempt.getnev() == alapnev){ //Ha van, de ezt nyitottuk meg, akkor fel�l�rjuk
                                tipusok[vane] = tempt;
                                for (int i = 0; i < elemszam[1]; i++)
                                    if (erzekelok[i].geterztip().getnev() == tempt.getnev())
                                        erzekelok[i].seterztip(tempt);
                                econio_clrscr();
                                std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                            else {  //Egy�bk�nt nem menthet
                                econio_clrscr();
                                std::cout << "M�r van ilyen nev� t�pus!\n(folytat�shoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                        }
                        else {  //Ha nincs elmentj�k
                            elemszam[2]++;
                            ErzTipus *uj = new ErzTipus[elemszam[2]];
                            for (size_t i = 0; (int)i < elemszam[2] - 1; i++)
                                uj[i] = tipusok[i];
                            uj[elemszam[2] - 1] = tempt;
                            delete[] tipusok;
                            tipusok = uj;
                            kcurrent = elemszam[2] - 1;
                            econio_clrscr();
                            std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
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
                        std::cout << "Ezt nem lehet t�r�lni!\n(folytat�shoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else { //T�rl�s, ha nincs haszn�lva �s l�tezik ilyen nev�
                        int idx = -1;
                        for (int i = 0; i < elemszam[2]; i++)
                            if (tipusok[i].getnev() == tempt.getnev())
                                idx = i;
                        if (idx == -1) {
                            econio_clrscr();
                            std::cout << "Nincs ilyen nev� t�pus!\n(folytat�shoz nyomj entert)";
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
                                std::cout << "Ez a t�pus haszn�latban van! Csak nem haszn�ltat lehet t�r�lni.\n(folytat�shoz nyomj entert)";
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
                                std::cout << "Sikeres t�rl�s.\n(folytat�shoz nyomj entert)";
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

        if (allapot == 7) { //Szir�na szerkeszt�se
            String alapnev;
            Szirena alap;
            if (kcurrent == elemszam[3])
                alapnev = alap.getnev();
            else
                alapnev = szirenak[kcurrent].getnev();

            {   //Men� ki�r�sa

            std::cout << "�rz�kel� szerkeszt�se\nN�v:" << alapnev << "\n\n";

            if (current == 0) {
                jelenlegi("N�v: ");
                jelenlegi(temps.getnev());
            }
            else
                std::cout << "N�v: " << temps.getnev();
            std::cout << "\n";

            if (current == 1) {
                jelenlegi("Id�zit�s: ");
                jelenlegi(temps.getidoz());
            }
            else
                std::cout << "Id�zit�s: " << temps.getidoz();
            std::cout << "\n";

            std::cout << "Logika: ";
            if (temps.getlogika() != 0) std::cout << temps.getlogika()->getnev();
            std::cout << "\n";

            if (current == 2)
                if (alkcurrent == -1) {
                    jelenlegi("v Logik�k:\n");
                    logiklistaz(logikak, elemszam[0], alkcurrent, false);
                }
                else {
                    std::cout << "v Logik�k:\n";
                    logiklistaz(logikak, elemszam[0], alkcurrent, false);
                }
            else {
                std::cout << "v Logik�k:\n";
                logiklistaz(logikak, elemszam[0], -1, false);
            }

            std::cout << "Olvas�: ";
            if (temps.getolvas() != 0) std::cout << temps.getolvas()->getnev();
            std::cout << "\n";

            if (current == 3)
                if (alkcurrent == -1) {
                    jelenlegi("v Olvas�k:\n");
                    olvlistaz(kodolvasok, elemszam[4], alkcurrent, false);
                }
                else {
                    std::cout << "v Olvas�k:\n";
                    olvlistaz(kodolvasok, elemszam[4], alkcurrent, false);
                }
            else {
                std::cout << "v Olvas�k:\n";
                olvlistaz(kodolvasok, elemszam[4], -1, false);
            }

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
            String nev = temps.getnev();

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

                if (get == 13 && current == 4) {    //Ment�s
                    if (temps.getnev() == "" || temps.getlogika() == 0 || temps.getolvas() == 0) { //Nem menthet n�v n�lk�l
                        econio_clrscr();
                            std::cout << "A n�v, a logika, vagy az olvas� nem lehet �res!\n(folytat�shoz nyomj entert)";
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
                                std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                                get = getcharwoent();
                                while(get != 13)
                                get = getcharwoent();
                                econio_clrscr();
                            }
                            else {
                                econio_clrscr();
                                std::cout << "M�r van ilyen nev� �rz�kel�!\n(folytat�shoz nyomj entert)";
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
                            std::cout << "Ment�s k�sz\n(folytat�shoz nyomj entert)";
                            get = getcharwoent();
                            while(get != 13)
                            get = getcharwoent();
                            econio_clrscr();
                        }
                    }
                }

                if (get == 13 && current == 5) {    //T�rl�s
                    if (kcurrent == elemszam[3]) {
                        econio_clrscr();
                        std::cout << "Ezt nem lehet t�r�lni!\n(folytat�shoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                    else {  //T�rl�s, mert �gysincs haszn�lva
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
                        std::cout << "Sikeres t�rl�s.\n(folytat�shoz nyomj entert)";
                        get = getcharwoent();
                        while(get != 13)
                            get = getcharwoent();
                        econio_clrscr();
                    }
                }

                if (get == 8 || (current == 6 && get == 13) || get == 'b') { //kil�p�s
                    allapot = 0;
                    current = 0;
                    kcurrent = -1;
                    econio_clrscr();
                }


                switch (current) {
                    case 2: //Logik�k k�z�tt l�pked
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
                    case 3: //Olvas�k k�z�tt l�pked
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
                    default: //Egy�bk�nt l�ptet
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
                    if (tempo.getnev() == "") { //Nem menthet n�v n�lk�l
                        econio_clrscr();
                            std::cout << "A n�v nem lehet �res!\n(folytat�shoz nyomj entert)";
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
                        if (vane != -1) { // ha van �tk�z�s
                            if (tempo.getnev() == alapnev){ // ha a jelenlegi az akkor menthetj�k, egy�bk�nt nem
                                kodolvasok[vane] = tempo;
                                for (int i = 0; i < elemszam[3]; i++)
                                    if (szirenak[i].getolvas()->getnev() == tempo.getnev())
                                        szirenak[i].setolvas(&tempo);
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
    if (szirenak != nullptr)
        delete[] szirenak;
    if (kodolvasok != nullptr)
        delete[] kodolvasok;


}
