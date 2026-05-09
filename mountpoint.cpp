#include <iostream>
#include "mountpoint.h"

using namespace std;


mountPoint :: mountPoint(char* n, User* o, char* gName, int cap) : Directory(n, o, gName, cap)
{
    mounted = nullptr;
}

void mountPoint :: mount(Partition* p) {
    if(mounted == nullptr)
    {   
        if(p != nullptr && p->getMountStatus() == false)
        {
            mounted = p;
            p->setMounted(true);
        }
        else
            cout << "\nPartition is already mounted at another location!" << endl;
    }
    else
        cout << "\nMount point is not free!" << endl;
}

void mountPoint :: unmount() {
    if(mounted != nullptr)
    {
        mounted->setMounted(false);
        mounted = nullptr;
    }
}

bool mountPoint :: hasPartition() {
    return (mounted != nullptr);
}

double mountPoint :: getSize() {
    double total = Directory :: getSize();

    if(mounted != nullptr)
        total += mounted->getUsedSpace();

    return total;
}

mountPoint :: ~mountPoint() {}
