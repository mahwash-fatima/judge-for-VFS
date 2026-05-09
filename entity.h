#ifndef ENTITY_H
#define ENTITY_H

#include <ctime>
#include "user.h"
#include "permissions.h"
#include "extendedattribute.h"


class fileSystemEntity {
    protected:
        char* name;
        User* owner;
        Permissions permissions;
        time_t creationTime;
        time_t modifiedTime;
        fileSystemEntity* parent;
        extendedAttribute** attr;
        int attrCount;
        int attrCapacity;
    public:
        fileSystemEntity(char* n = nullptr, User* o = nullptr, char* gName = nullptr);

        virtual double getSize() = 0;

        virtual void display(int depth = 0) = 0;

        char* getName();

        User* getOwnerName();

        time_t getCreationTime();

        time_t getModifiedTime();

        void setParent(fileSystemEntity* p);

        void addAttribute(extendedAttribute* newAttribute);

        bool removeAttribute(char* attrKey);

        extendedAttribute* findAttribute(char* targetKey);

        virtual ~fileSystemEntity();
};


#endif