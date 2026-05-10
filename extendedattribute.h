#ifndef EXTENDED_ATTRIBUTE_H
#define EXTENDED_ATTRIBUTE_H


class extendedAttribute {
    private:
        char* key;
        char* value;
    public:
        extendedAttribute(char* k, char* v);

        char* getKey();

        char* getValue();

        ~extendedAttribute();
};

#endif