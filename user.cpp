#include <iostream>
#include "user.h"
#include "helper.h"

using namespace std;

User::User(char* name, int id, char* path, char* role, Difficulty tier) {
    userID = id;
    userName = copyStr(name);
    directoryPath = copyStr(path);
    userRole = copyStr(role);
    assignedTier = tier;
}

int User::getUserId() {
    return userID;
}

char* User::getUserName() {
    return userName;
}

Difficulty User::getAssignedTier() {
    return assignedTier;
}

void User::setAssignedTier(Difficulty tier) {
    assignedTier = tier;
}

bool User::isRootUser() {
    char* tempRole = copyStr(userRole);
    toLower(tempRole);

    bool root = (tempRole[0] == 'r' && tempRole[1] == 'o' && tempRole[2] == 'o' && tempRole[3] == 't');
    
    delete[] tempRole;
    return root;
}

User::~User() {
    delete[] userName;
    delete[] directoryPath;
    delete[] userRole;
}
