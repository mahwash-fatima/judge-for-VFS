#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

class DynamicArray {
private:
    void** items;
    int capacity;
    int itemCount;

    void expandArray();

public:
    DynamicArray();
    DynamicArray(const DynamicArray& obj);
    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& obj);
    
    void addItem(void* item);
    void* getIndex(int index) const;
    int getCurrItems() const;
    void removeItem(int index);
};

#endif