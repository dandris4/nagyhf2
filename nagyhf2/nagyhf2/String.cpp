#include <string.h>

#include "String.h"
#include "memtrace.h"



String::String(char ch) {
    len = 1;
    pData = new char[len+1];
    pData[0] = ch;
    pData[1] = '\0';
}


String::String(const char *p) {
    len = strlen(p);
    pData = new char[len+1];
    strcpy(pData, p);
}

String::String(const String& s1) {
    len = s1.len;
    pData = new char[len+1];
    strcpy(pData, s1.pData);
}

String& String::operator=(const String& rhs_s) {
    if (this != &rhs_s) {
        delete[] pData;
        len = rhs_s.len;
        pData = new char[len+1];
        strcpy(pData, rhs_s.pData);
    }
    return *this;
}

String& String::operator+=(const char rhs_c) {
    len++;
    char *temp = new char[len + 1];
    strcpy(temp, pData);
    temp[len - 1] = rhs_c;
    temp[len] = '\0';
    delete[] pData;
    pData = temp;
    return *this;
}

String String::operator--(int i) {
    String temp(*this);
    char* ptemp = new char[len];
    len--;
    for (size_t i = 0; i < len; i++)
        ptemp[i] = pData[i];
    ptemp[len] = '\0';
    delete[] pData;
    pData = ptemp;
    return temp;
}

    bool String::operator!=(const char* be) {
        return strcmp(pData, be);
    }

    bool String::operator==(const char* be) {
        return !strcmp(pData, be);
    }
