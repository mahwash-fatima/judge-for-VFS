#include <iostream>
#include "helper.h"
#include "entity.h"
#include "directory.h"
#include "file.h"

using namespace std;



Directory :: Directory(char* n, User* o, char* gName, int cap) : fileSystemEntity(n, o, gName) {
    
    capacity = (cap > 0)? cap : 50;
    itemCount = 0;

    entities = new fileSystemEntity* [capacity];

    for(int i = 0; i < capacity; i++)
        entities[i] = nullptr;
}


double Directory :: getSize() {
    double total = 0.0;

    for(int i = 0; i < capacity; i++)
    {
        if(entities[i] != nullptr)
        {
           total += entities[i]->getSize();
        }
    }
    return total;
}

int Directory :: getItemCount() {
    return itemCount;
}


void Directory::addEntity(fileSystemEntity* entity) {
    // Check 1: Number of slots (Items)
    if (itemCount >= capacity) {
        cout << "Directory capacity is full! Entity cannot be added." << endl;
        return;
    }

    // If the file is 20000MB (20GB) or more, block it
    if (entity->getSize() >= 20000) { 
        cout << "Storage capacity exceeded! Cannot add " << entity->getName() << " (File too large)." << endl;
        return;
    }
    entities[itemCount++] = entity;
}

bool Directory::removeEntity(char* entity) {
    for (int i = 0; i < itemCount; i++) {
        if (entities[i] != nullptr)
        {
            if(compareStr(entities[i]->getName(), entity))
            {
                entities[i]->setParent(nullptr);

                for (int j = i; j < itemCount - 1; j++) {
                    entities[j] = entities[j + 1];
                }

                entities[itemCount - 1] = nullptr;
                itemCount--;

                modifiedTime = time(0);

                return true;
            }
        }
    }
    return false;
}

fileSystemEntity* Directory::findEntity(char* name) {
    if (name == nullptr) return nullptr;

    for (int i = 0; i < itemCount; i++) {
        if (entities[i] == nullptr) continue;

        // 1. Check the current folder level
        if (compareStr(entities[i]->getName(), name)) {
            return entities[i];
        }

        Directory* subDir = dynamic_cast<Directory*>(entities[i]);
        if (subDir != nullptr) {
            fileSystemEntity* found = subDir->findEntity(name);
            if (found != nullptr) return found;
        }
    }
    return nullptr;
}

bool Directory::moveEntity(char* entityName, Directory* destination) {
    for (int i = 0; i < itemCount; i++) {
        if (entities[i] != nullptr && compareStr(entities[i]->getName(), entityName)) {

            destination->addEntity(entities[i]);
            
            for (int j = i; j < itemCount - 1; j++) {
                entities[j] = entities[j + 1];
            }
            entities[itemCount - 1] = nullptr;
            itemCount--;
            return true;
        }
    }
    return false;
}

void Directory::copyFile(File* original, Directory* destination, char* newName, User* owner) {
    File* copiedFile = new File(newName, owner, (char*)"users", (char*)"Copy of original");
    destination->addEntity(copiedFile);
}

void Directory::display(int depth) {
    // Print the folder itself
    for (int i = 0; i < depth; i++) cout << "    ";
    cout << "FOLDER: " << getName() << endl;

    for (int i = 0; i < itemCount; i++) {
        if (entities[i] != nullptr) {
            entities[i]->display(depth + 1);
        }
    }
}

Directory :: ~Directory() {
    if(entities != nullptr)
    {
        for(int i = 0; i < capacity; i++)
        {
            if(entities[i] != nullptr)
                delete entities[i];
        }
        delete[] entities;
    }
}

