#ifndef STRING_H
#define STRING_H

#include <iostream>


class String {
    char *pData;
    size_t len;
public:


    // Hossz lek�rdez�se.
    // return :len
	size_t size() const;

    // String pointer�t adja vissza
    // return: pData
    const char* c_str() const { return pData;}

    // Konstruktor egy char karakterb�l
    // @param ch - karakter
    String(const char ch);

    // Konstruktor \0-al lez�rt
    // p: pointer
    String(const char *p = "");

    // M�sol� konstruktor
    String(const String& s1);

    // �rt�kad� oper�tor.
    // Ugyanaz, mint a m�sol�
    String& operator=(const String& rhs_s);

    //String v�g�re karaktert f�z
    String& operator+=(const char rhs_c);

    //String v�g�re Stringet f�z
    String& operator+=(const String rhs_s);

    //String utols� elem�t kit�rli
    String operator--(int i);

    //�sszehasonl�t�s
    bool operator!=(const char* be);

    //�sszehasonl�t�s
    bool operator==(const char* be);

    // Destruktor
    virtual ~String() { delete[] pData; }

};

std::ostream& operator<<(std::ostream& os, String str);

#endif
