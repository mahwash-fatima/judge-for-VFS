#include <iostream>
#include "partition.h"
#include "storage.h"
#include "helper.h"

using namespace std;



Partition :: Partition(char* l, char* f, double cap, storageMedium* parent) {
    parentMedium = parent;
    usedSpace = 0.0;
    isMounted = false;

    if(parent != nullptr && cap <= parent->getRemainingCapacity())
    {
        capacity = cap;
    }
    else
    {
        capacity = 0.0;
        cout << "Storage medium does not have enough capacity to create another partition!" << endl;
    }

    int len1 = 0;
    if(l != nullptr)
    {
        while(l[len1] != '\0')
            len1++;
        label = new char [len1 + 1];
        label = copyStr(l);
    }
    else 
        label = nullptr;
        
    if(l != nullptr)
    {
        int len2 = 0;
        while(f[len2] != '\0')
            len2++;
        format = new char [len2 + 1];
        format = copyStr(f);
    }
    else
        format = nullptr;

}

double Partition :: getUsedSpace() const {
    return usedSpace;
}

double Partition :: getCapacity() const {
    return capacity;
}

bool Partition ::getMountStatus() const {
    return isMounted;
}

bool Partition :: setMounted(bool status) {
    return isMounted = status;
}

bool Partition :: addData(double size) {
    if (usedSpace + size <= capacity)
    {
        usedSpace += size;
        return true;
    }
    return false;
}

Partition :: ~Partition() {
    delete[] label;
    delete[] format;
}