#include <iostream>
#include "entity.h"
#include "helper.h"

using namespace std;


fileSystemEntity :: fileSystemEntity(char* n, User* o, char* gName) : permissions(gName) {
    name = copyStr(n);
    owner = o;
    creationTime  = time(0);
    modifiedTime = time(0);

    attrCount = 0;
    attrCapacity = 20;

    parent = nullptr;

    attr = new extendedAttribute* [attrCapacity];

    for(int i = 0; i < attrCapacity; i++)
        attr[i] = nullptr;
}

char* fileSystemEntity :: getName() {
    if(name == nullptr)
        return (char*)"Unnamed!";
    return name;
}

User* fileSystemEntity :: getOwnerName() {
    return owner;
}

time_t fileSystemEntity :: getCreationTime() {
    return creationTime;
}

time_t fileSystemEntity :: getModifiedTime() {
    return modifiedTime;
}

void fileSystemEntity :: setParent(fileSystemEntity* p) {
    parent = p;
}

void fileSystemEntity :: addAttribute(extendedAttribute* newAttribute) {
    if(attrCount < attrCapacity)
    {
        attr[attrCount] = newAttribute;
        attrCount++;
    }
    else
        cout << "\nCapacity full! Attribute cannot be added." << endl;
}

bool fileSystemEntity :: removeAttribute(char* attrKey) {
    for (int i = 0; i < attrCount; i++) {
        if (attr[i] != nullptr)
        {
            if(compareStr(attr[i]->getKey(), attrKey))
            {
                delete attr[i];

                for (int j = i; j < attrCount - 1; j++) {
                    attr[j] = attr[j + 1];
                }

                attr[attrCount - 1] = nullptr;
                attrCount--;

                return true;
            }
        }
    }
    return false;
}

extendedAttribute* fileSystemEntity :: findAttribute(char* targetKey) {
    for(int i = 0; i < attrCount; i++)
    {
        if(attr[i] != nullptr)
        {
            if(compareStr(attr[i]->getKey(), targetKey))
                return attr[i];
        }
    }
    return nullptr;
}

fileSystemEntity :: ~fileSystemEntity() {
    if(attr != nullptr)
    {
        for(int i = 0; i < attrCapacity; i++)
        {
            if(attr[i] != nullptr)
                delete attr[i];
        }
        delete[] attr;
    }   

    delete[] name;
}