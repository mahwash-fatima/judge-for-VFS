#include "extendedattribute.h"
#include "helper.h"


extendedAttribute :: extendedAttribute(char* k, char* v)
{
    key = copyStr(k);
    value = copyStr(v);
}

char* extendedAttribute :: getKey() {
    return key;
}

char* extendedAttribute :: getValue() {
    return value;
}

extendedAttribute :: ~extendedAttribute() {
    delete[] key;
    delete[] value;
}