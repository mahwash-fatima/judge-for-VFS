#include <iostream>
#include "helper.h"
#include "entity.h"
#include "symblink.h"

using namespace std;


symbLink :: symbLink(char* n, User* o, char* gName, fileSystemEntity* target) : fileSystemEntity(n, o, gName)
{
    targetPath = target;
}

double symbLink :: getSize() {
    return 0.0;
}

bool symbLink :: checkDangling() {
    if(targetPath == nullptr)
        return true;
    else
        return false;
}

fileSystemEntity* symbLink :: getTargetPath() {
    return targetPath;
}

void symbLink::display(int depth) {
    for (int i = 0; i < depth; i++) cout << "    ";
    cout << "LINK: " << getName() << " -> (Target Pointed)" << endl;
}

void symbLink::setTargetPath(fileSystemEntity* target) {
    targetPath = target;
}

symbLink :: ~symbLink() {}