#include <iostream>
#include "user.h"
#include "helper.h"

using namespace std;


User :: User(char* name, int id, char* path, char* role)
{
    userID = id;
    userName = copyStr(name);
    directoryPath = copyStr(path);
    userRole = copyStr(role);
}

int User :: getUserId() {
    return userID;
}

char* User :: getUserName() {
    return userName;
}

bool User :: isRootUser() {
    toLower(userRole);

    if(userRole[0] == 'r' && userRole[1] == 'o' && userRole[2] == 'o' && userRole[3] == 't')
        return true;

    return false;
}

User :: ~User() {
    delete[] userName;
    delete[] directoryPath;
    delete[] userRole;
}