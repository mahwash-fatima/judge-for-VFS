#ifndef LINKED_LIST_H
#define LINKED_LIST_H


class Node {
public:
    void* data;
    Node* next;

    Node(void* item);
};

class LinkedList {
private:
    Node* head;
    int itemCount;

public:
    LinkedList();
    ~LinkedList();

    LinkedList(const LinkedList& obj);
    LinkedList& operator=(const LinkedList& obj);

    void addAtStart(void* item);
    void* getItem(int index) const;
    int getListSize() const;
    void removeItem(int index);
    void removeAll();
};

#endif