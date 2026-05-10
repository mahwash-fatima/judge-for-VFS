#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H

#include "String.h"

class HashEntry {
private:
    String key;
    void* value;

public:
    HashEntry(String key, void* value) {
        key = key;
        value = value;
    }

    String getKey() const { 
        return key; 
    }

    void* getValue() const { 
        return value; 
    }
};

#endif