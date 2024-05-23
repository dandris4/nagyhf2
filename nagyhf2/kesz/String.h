#ifndef STRING_H
#define STRING_H

#include <iostream>


class String {
    char *pData;
    size_t len;
public:


    // Hossz lekérdezése.
    // return :len
	size_t size() const;

    // String pointerét adja vissza
    // return: pData
    const char* c_str() const { return pData;}

    // Konstruktor egy char karakterbõl
    // @param ch - karakter
    String(const char ch);

    // Konstruktor \0-al lezárt
    // p: pointer
    String(const char *p = "");

    // Másoló konstruktor
    String(const String& s1);

    // Értékadó operátor.
    // Ugyanaz, mint a másoló
    String& operator=(const String& rhs_s);

    //String végére karaktert füz
    String& operator+=(const char rhs_c);

    //String végére Stringet füz
    String& operator+=(const String rhs_s);

    //String utolsó elemét kitörli
    String operator--(int i);

    //Összehasonlítás
    bool operator!=(const char* be);

    //Összehasonlítás
    bool operator==(const char* be);

    // Destruktor
    virtual ~String() { delete[] pData; }

};

std::ostream& operator<<(std::ostream& os, String str);

#endif
