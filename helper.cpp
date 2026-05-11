#include <iostream>
#include "helper.h"

using namespace std;

//definition for copyStr helper func
char* copyStr(const char* source) {
    if(source == nullptr)
    {
        cout << "The source string is empty! Contents cannot be copied." << endl;
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

//definition for compare str helper func
bool compareStr(const char* str1, const char* str2) {
    if(str1 == str2)
        return true;

    if(str1 == nullptr || str2 == nullptr)
        return false;

    int len1 = 0;
    while(str1[len1] != '\0')
        len1++;

    int len2 = 0;
    while(str2[len2] != '\0')
        len2++;

    if(len1 != len2)
        return false;

    for(int i = 0; i < len1; i++)
    {
        if(str1[i] != str2[i])
            return false;
    }
    
    // Return true only if both strings reached the null terminator
    return true;
}
