#include "HashTable.h"
#include "HashEntry.h"

HashTable::HashTable(int size) {
    count = size;
    table = new LinkedList[count];
}

HashTable::~HashTable() {
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < table[i].getListSize(); j++)
        {
            HashEntry* entry = (HashEntry*)table[i].getItem(j);
            delete entry;
        }
    }
    delete[] table;
}

int HashTable::hashFunc(const String& key) const {
    int hash = 0;

    const char* str = key.getString();
    for (int i = 0; i < key.getLength(); i++)
    {
        hash = (hash * 31 + str[i]) % count;
    }
    return hash;
}

void HashTable::insert(const String& key, void* value) {
    int index = hashFunc(key);

    HashEntry* newEntry = new HashEntry(key, value);
    table[index].addAtStart(newEntry);
}

void* HashTable::search(const String& key) const {
    int index = hashFunc(key);
    LinkedList& slot = table[index];
    
    for (int i = 0; i < slot.getListSize(); i++)
    {
        HashEntry* entry = (HashEntry*)slot.getItem(i);

        if (entry->getKey() == key)
            return entry->getValue();
    }
    return nullptr;
}

void HashTable::remove(const String& key) {
    int index = hashFunc(key);
    LinkedList& slot = table[index];

    for (int i = 0; i < slot.getListSize(); i++)
    {
        HashEntry* entry = (HashEntry*)slot.getItem(i);
        
        if (entry->getKey() == key)
        {
            delete entry;
            
            slot.removeItem(i); 
        }
    }
}