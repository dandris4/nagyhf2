#include <string.h>
#include <math.h>

#include "String.h"
#include "memtrace.h"


size_t String::size() const {
    return len;
}

String::String(const char ch) {
    len = 1;
    pData = new char[len+1];
    pData[0] = ch;
    pData[1] = '\0';
}

String::String(int be) {
    if (be == 0) {
        len = 1;
        pData = new char[len+1];
        pData[0] = '0';
        pData[1] = '\0';
    }
    else
    {
        bool m = be < 0;
        if (m)
            be = - be;
        int i = be, hossz = 0;
        for (; i >= 10; i = i / 10)
            hossz++;
        String tmp("");
        if (m)
            tmp += '-';
        for (;hossz >= 0; hossz--) {
            tmp += '0' + be / (int)pow(10, hossz);
            be = be % (int)pow(10, hossz);
        }
        len = tmp.len;
        pData = new char[len + 1];
        strcpy(pData,tmp.pData);
    }

}

String::String(const char *p) {
    len = strlen(p);
    pData = new char[len + 1];
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

String& String::operator+=(const String rhs_s) {
    len += rhs_s.len;
    char *temp = new char[len + 1];
    strcpy(temp, pData);
    strcpy(&temp[len - rhs_s.len], rhs_s.pData);
    delete[] pData;
    pData = temp;
    return *this;
}

String String::operator--(int i) {
    if (len != 0) {
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
    else
        return *this;
}

    bool String::operator!=(const char* be) const{
        return strcmp(pData, be);
    }

    bool String::operator==(const char* be) const{
        return !strcmp(pData, be);
    }

    bool String::operator!=(const String& be) const{
        return strcmp(pData, be.pData);
    }

    bool String::operator==(const String& be) const{
        return !strcmp(pData, be.pData);
    }

    std::ostream& operator<<(std::ostream& os, String str) {
        os << str.c_str();
        return os;
    }

    std::istream& operator>>(std::istream& os, String& str) {
        std::string a;
        os >> a;
        str = String(&a[0]);
        return os;
    }

