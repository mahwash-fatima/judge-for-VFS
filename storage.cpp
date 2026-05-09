#include <iostream>
#include "storage.h" //including the storage.h file which contains storageMedium class declaration
#include "partition.h" //including the partition.h file which contains Partition class declaration
#include "helper.h"

using namespace std;


//the three members in () have default values and the user can enter their choice, while some are initialized to 0 or nullptr in member initializer list
storageMedium :: storageMedium(double total, char* type, bool m) : totalMemory(total), mounted(m), usedMemory(0.0), partitions(nullptr), partitionCount(0), techType(nullptr)
{
    if(type != nullptr)
    {
        techType = copyStr(type); //helper func
    }
    else
        techType = nullptr;
}

double storageMedium :: getCapacity() {
    return totalMemory;
}

//calculates and returns the remaining memory in the storage medium
double storageMedium :: getRemainingCapacity() {
    return totalMemory - usedMemory;
}

//mounts the device
void storageMedium :: mount() {
    mounted = true;
}

//unmounts the device
void storageMedium :: unmount() {
    mounted = false;
}

//adds a partition to the device if there is enough space and if the device is mounted
void storageMedium :: addPartition(double newMemory, char* label, char* format) {
    if(!mounted)
    {
        cout << "The storage device is not mounted! Mount the device to perform operations." << endl;
        return;
    }
    else
    {
        if(newMemory <= getRemainingCapacity())
        {
            Partition** newPartition = new Partition*[partitionCount + 1];

            for(int i = 0; i < partitionCount; i++)
                newPartition[i] = partitions[i];

            newPartition[partitionCount] = new Partition(label, format, newMemory, this);

            delete[] partitions;

            partitions = newPartition;
            partitionCount++;
            usedMemory += newMemory;
        }
        else
        {
            cout << "\nStorage capacity is full! No more partitions can be added." << endl;
            return;
        }
    }
}

//finds a partition at a particular index and returns it
Partition* storageMedium::getPartition(int index) {
    if (index >= 0 && index < partitionCount) {
        return partitions[index];
    }

    cout << "Error: Partition index " << index << " out of bounds." << endl;
    return nullptr;
}

//deletes the data, the partitions and the device itself from memory
storageMedium :: ~storageMedium() {
    for(int i = 0; i < partitionCount; i++)
        delete partitions[i];

    delete[] partitions;

    delete[] techType;
}