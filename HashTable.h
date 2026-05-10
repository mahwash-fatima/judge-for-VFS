#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "String.h"
#include "LinkedList.h"

class HashTable {
private:
    LinkedList* table;
    int count;

    int hashFunc(const String& key) const;

public:
    HashTable(int count = 101);
    ~HashTable();

    void insert(const String& key, void* value);
    void* search(const String& key) const;
    void remove(const String& key);
};

#endif