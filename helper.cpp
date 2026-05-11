#include <iostream>
#include "helper.h"

using namespace std;

// Updated to use const char* to match helper.h
char* copyStr(const char* source) {
    if(source == nullptr) {
        return nullptr;
    }
    
    int len = 0;
    while(source[len] != '\0')
        len++;

    char* destination = new char[len + 1];
    for(int i = 0; i < len; i++)
        destination[i] = source[i];
    
    destination[len] = '\0';
    return destination;
}

void toLower(char* str) {
    if(str == nullptr) return;

    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
}

// Updated to use const char* to match helper.h
bool compareStr(const char* str1, const char* str2) {
    if(str1 == str2) return true;
    if(str1 == nullptr || str2 == nullptr) return false;

    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) return false;
        i++;
    }
    
    // Return true only if both strings reached the null terminator
    return (str1[i] == '\0' && str2[i] == '\0');
}
