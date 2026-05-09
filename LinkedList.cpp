#include "LinkedList.h"


Node ::Node(void* item) {
    data = item;
    next = nullptr;
}

LinkedList :: LinkedList() {
    head = nullptr;
    itemCount = 0;
}

void LinkedList :: addAtStart(void* item) {
    Node* newNode = new Node(item);

    newNode->next = head;
    head = newNode;

    itemCount++;
}

void LinkedList::removeItem(int index) {
    if (index < 0 || index >= itemCount)
        return;

    Node* toDelete = nullptr;

    if (index == 0)
    {
        toDelete = head;
        head = head->next;
    }
    else
    {
        Node* prev = head;
        for (int i = 0; i < index - 1; i++)
            prev = prev->next;
            
        toDelete = prev->next;
        prev->next = toDelete->next;
    }

    delete toDelete;
    itemCount--;

}

void LinkedList :: removeAll() {
    Node* current = head;

    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    itemCount = 0;
}

LinkedList :: ~LinkedList() {
    removeAll();
}

void* LinkedList :: getItem(int index) const {
    if(index < 0 || index >= itemCount)
        return nullptr;

    Node* current = head;
    for (int i = 0; i < index; i++)
        current = current->next;

    return current->data;
}

int LinkedList :: getListSize() const {
    return itemCount;
}

LinkedList :: LinkedList(const LinkedList& obj) {
    head = nullptr;
    itemCount = 0;

    if (obj.head == nullptr)
        return;

    addAtStart(obj.head->data); 
    
    Node* currentSource = obj.head->next;
    Node* lastAdded = head;

    while (currentSource != nullptr) {
        Node* newNode = new Node(currentSource->data);
        lastAdded->next = newNode;
        lastAdded = newNode;
        currentSource = currentSource->next;
        itemCount++;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& obj) {
    if (this != &obj)
    {
        removeAll();

        if (obj.head != nullptr)
        {
            addAtStart(obj.head->data);

            Node* currentSource = obj.head->next;
            Node* lastAdded = head;

            while (currentSource != nullptr)
            {
                Node* newNode = new Node(currentSource->data);
                lastAdded->next = newNode;
                lastAdded = newNode;
                currentSource = currentSource->next;
                itemCount++;
            }
        }
    }
    return *this;
}