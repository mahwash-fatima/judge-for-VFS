#include <iostream>
#include "volume.h"
#include "helper.h"

using namespace std;



Volume :: Volume(char* name)
{
    volName = copyStr(name);

    userCapacity = 20; userCount = 0;
    userRegistry = new User* [userCapacity];

    partitionCapacity = 20; partitionCount = 0;
    mountedPartitions = new Partition* [partitionCapacity];

    deviceCapacity = 20; deviceCount = 0;
    deviceList = new storageMedium* [deviceCapacity];

    User* admin = new User((char*)"root", 0, (char*)"/", (char*)"admin");
    registerUser(admin);

    rootDirectory = new Directory((char*)"/", admin, (char*)"system");
}

bool Volume :: registerUser(User* newUser) {
    if(newUser == nullptr)
        return false;

    for(int i = 0; i < userCount; i++)
    {
        if(userRegistry[i]->getUserId() == newUser->getUserId())
            return false;
    }

    if(userCount < userCapacity)
    {
        userRegistry[userCount] = newUser;
        userCount++;
        return true;
    }
    return false;
}

User** Volume :: getUserRegistry() { 
    return userRegistry;
}

bool Volume :: addStorageMedium(storageMedium* device) {
    if(device == nullptr)
        return false;

    if(deviceCount < deviceCapacity)
    {
        deviceList[deviceCount] = device;
        deviceCount++;
        return true;
    }
    return false;
}

bool Volume :: mountPartition(Partition* p, Directory* mountPnt) {
    if(p == nullptr || mountPnt == nullptr)
        return false;

    if(partitionCount < partitionCapacity)
    {
        if (p->getMountStatus()) 
            return false;

        mountedPartitions[partitionCount] = p;
        partitionCount++;

        p->setMounted(true);

        return true;
    }
    return false;
}

bool Volume :: isNameUnique(Directory* parent, char* name) {
    if(parent == nullptr || name == nullptr)
        return false;

    if(parent->findEntity(name) == nullptr)
        return true;

    return false;
}

bool Volume :: IsOwnerRegistered(User* u) {
    if(u == nullptr)
        return false;

    for(int i = 0; i < userCount; i++)
    {
        if(userRegistry[i] == u)
            return true;
    }
    return false;
}

double Volume :: getCombinedCapacity() {
    double total = 0.0;

    for(int i = 0; i < deviceCount; i++)
        total += deviceList[i]->getCapacity();

    return total;
}

double Volume :: getTotalUsedSpace() {
    double totalSpaceUsed = 0.0;

    for(int i = 0; i < partitionCount; i++)
        totalSpaceUsed += mountedPartitions[i]->getUsedSpace();

    return totalSpaceUsed;
}

Directory* Volume :: getRoot() {
    return rootDirectory;
}

User* Volume :: getUser(int id) {
    for(int i = 0; i < userCount; i++)
    {
        if(userRegistry[i]->getUserId() == id)
            return userRegistry[i];
    }
    return nullptr;
}

void Volume :: displaySystemSummary() {
    cout << "\nSYSTEM SUMMARY" << endl;

    int currentUsage = rootDirectory->getSize();

    cout << "Volume name: " << volName << endl;
    cout << "No. of users registered: " << userCount << endl;
    cout << "Storage used: " << currentUsage<< " out of " << getCombinedCapacity() << " mbs used" << endl;
    cout << "Partitions status: " << (partitionCount > 0 ? "Active" : "No Partitions Mounted") << endl;
}

void Volume::displayUserRegistry() {
    cout << "\nUSER REGISTRY" << endl;

    for (int i = 0; i < userCount; i++) {
        cout << "[" << i + 1 << "] Name: " << userRegistry[i]->getUserName() 
             << " (ID: " << userRegistry[i]->getUserId() << ")" << endl;
    }
}

Volume :: ~Volume() {

    delete[] volName;

    delete rootDirectory;

    if(userRegistry != nullptr)
    {
        for(int i = 0; i < userCapacity; i++)
        {
            if(userRegistry[i] != nullptr)
                delete userRegistry[i];
        }
        delete userRegistry;
    }    

    delete deviceList;
    delete mountedPartitions;

}