#include "DynamicArray.h"


void DynamicArray :: expandArray() {
    capacity *= 2;

    void** temp = new void* [capacity];
    for(int i = 0; i < itemCount; i++)
        temp[i] = items[i];

    delete[] items;
    items = temp;
}


DynamicArray :: DynamicArray() {
    capacity = 3;
    itemCount = 0;
    items = new void* [capacity];
}

DynamicArray :: ~DynamicArray() {
    delete[] items;
}

DynamicArray :: DynamicArray(const DynamicArray& obj) {
    capacity = obj.capacity;
    itemCount = obj.itemCount;

    items = new void* [capacity];
    for(int i = 0; i < itemCount; i++)
        items[i] = obj.items[i];
}

DynamicArray& DynamicArray :: operator=(const DynamicArray& obj) {
    if(this != &obj)
    {
        delete[] items;

        capacity = obj.capacity;
        itemCount = obj.itemCount;

        items = new void* [capacity];
        for(int i = 0; i < itemCount; i++)
            items[i] = obj.items[i];
    }
    return *this;
}

void DynamicArray :: addItem(void* item) {
    if(itemCount == capacity)
        expandArray();

    items[itemCount] = item;
    itemCount++; 
}

void* DynamicArray :: getIndex(int index) const {
    if(index >= 0 && index < itemCount)
        return items[index];

    return nullptr;   
}

int DynamicArray :: getCurrItems() const {
    return itemCount;
}

void DynamicArray::removeItem(int index) {
    if (index < 0 || index >= itemCount) return;
    for (int i = index; i < itemCount - 1; i++)
        items[i] = items[i + 1];
    items[--itemCount] = nullptr;
}