#include "permissions.h"
#include "user.h"
#include "helper.h"

Permissions :: Permissions(char* gName) {
    groupName = copyStr(gName);

    //Owner has access to all
    ownerPermissions[0] = true; //read
    ownerPermissions[1] = true; //write
    ownerPermissions[2] = true; //execute

    //Group can only read/execute
    groupPermissions[0] = true; //read
    groupPermissions[1] = false; //write
    groupPermissions[2] = true; //execute

    //Others can only read
    otherPermissions[0] = true; //read
    otherPermissions[1] = false; //write
    otherPermissions[2] = false; //execute 
}


bool Permissions :: canRead(User* accessor, User* owner) {
    //if the accessor is a root (super) user then they have access
    if(accessor != nullptr && accessor->isRootUser())
        return true;

    //returning owner permissions if accessor is the owner
    if(accessor == owner)
        return ownerPermissions[0];

    //group one for later

    //if none of the above conditions meet it means that the accssor is others and the permissions are returned accordingly
    return otherPermissions[0];
}

bool Permissions :: canWrite(User* accessor, User* owner) {
    //if the accessor is a root (super) user then they have access
    if(accessor != nullptr && accessor->isRootUser())
        return true;

    //returning owner permissions if accessor is the owner
    if(accessor == owner)
        return ownerPermissions[1];

    //group one for later

    //if none of the above conditions meet it means that the accssor is others and the permissions are returned accordingly
    return otherPermissions[1];
}

bool Permissions :: canExecute(User* accessor, User* owner) {
    //if the accessor is a root (super) user then they have access
    if(accessor != nullptr && accessor->isRootUser())
        return true;

    //returning owner permissions if accessor is the owner
    if(accessor == owner)
        return ownerPermissions[2];

    //group one for later

    //if none of the above conditions meet it means that the accssor is others and the permissions are returned accordingly
    return otherPermissions[2];
}


Permissions :: ~Permissions() {
    delete[] groupName;
}