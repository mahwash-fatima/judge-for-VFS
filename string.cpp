#include "String.h"


int String :: calculateLen(const char* str) const {
    int len = 0;

    while(str[len] != '\0')
        len++;

    return len;
}

char* String :: copyStr(const char* source) {
    if(source == nullptr)
        return nullptr;
    else
    {
        strLen = calculateLen(source);

        char* destination = new char[strLen + 1];
        for(int i = 0; i < strLen; i++)
            destination[i] = source[i];
        
        destination[strLen] = '\0';
        return destination;
    }
}

String :: String() : strLen(0) {
    data = new char[1];
    data[0] = '\0';
}

String::String(const char* str) {
    data = copyStr(str);
}

String::String(const String& obj) {
    data = copyStr(obj.data);
}

String :: ~String() {
    delete[] data;
}

String& String::operator=(const String& obj) {
    if (this != &obj)
    {
        delete[] data;

        data = copyStr(obj.data);
    }
    return *this;
}

bool String :: operator==(const String& obj) const {
    if (strLen != obj.strLen)
        return false;

    for (int i = 0; i < strLen; i++)
    {
        if (data[i] != obj.data[i])
            return false;
    }
    return true;
}

const char* String :: getString() const {
    return data;
}

int String :: getLength() const {
    return strLen;
}