#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "entity.h"

class fileSystemEntity;
class User;

class File;  

class Directory : public fileSystemEntity{
    private:
        fileSystemEntity** entities;
        int itemCount;
        int capacity;
    public:
        Directory(char* n, User* o, char* gName, int cap = 50);

        virtual double getSize() override;

        int getItemCount();

        void addEntity(fileSystemEntity* newEntity);

        bool removeEntity(char* entity);

        fileSystemEntity* findEntity(char* targetEntity);

        bool moveEntity(char* entityName, Directory* destination);

        void copyFile(File* original, Directory* destination, char* newName, User* owner);

        void display(int depth);

        virtual ~Directory() override;
};


#endif