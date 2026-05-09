#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include "user.h"

class Permissions {
    private:
        char* groupName;
        bool ownerPermissions[3]; // [0] = read, [1] = write, [2] = execute
        bool groupPermissions[3];
        bool otherPermissions[3];
    public:
        Permissions(char* name);

        bool canRead(User* accessor, User* owner);
        
        bool canWrite(User* accessor, User* owner);

        bool canExecute(User* accessor, User* owner);

        ~Permissions();
};


#endif