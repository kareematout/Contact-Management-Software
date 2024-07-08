#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include "Contacts.h"

using namespace std;

struct LinkNode {
    Contacts *data = nullptr;
    LinkNode *next = nullptr;
};

class SinglyLinkedList
{
private:
    LinkNode *start = nullptr, *end = nullptr;
    int count;

public:
    SinglyLinkedList();   // constructor
    ~SinglyLinkedList();  // destructor

    // Linked list operations
    void insertContact(Contacts&);
    Contacts& removeContact(Contacts);
    Contacts& removeContact(int);
    int findContact(Contacts) const;
    Contacts getContact(int) const;
    void printList() const;
    bool isListEmpty() const {return (start == nullptr);}
    int Count() const {return count;}
    void replaceContact(Contacts oldContact, Contacts newContact);
};

SinglyLinkedList::SinglyLinkedList() {
    count = 0;
}

SinglyLinkedList::~SinglyLinkedList() {
    LinkNode *pCur;
    LinkNode *pNext;
    
    pCur = start;
    
    while (pCur) {
        pNext = pCur->next;
        delete pCur;
        pCur = pNext;
    }
}


void SinglyLinkedList::insertContact(Contacts& dataIn)
{
    LinkNode *newNode;
    LinkNode *pCur;
    LinkNode *pPre;
    
    newNode = new LinkNode;
    newNode->data = &dataIn;
    if (start == nullptr) {
        start = newNode;
        end = newNode;
        return;
    }
    pPre = start;
    pCur = start->next;
    
    
    while (pCur != NULL && pCur->data->getName() < dataIn.getName()) {
        pPre = pCur;
        pCur = pCur->next;
    }
    
    pPre->next = newNode;
    newNode->next = pCur;

    if (newNode->next == nullptr) {
        end = newNode;
    }
    
    count++;
}


Contacts& SinglyLinkedList::removeContact(Contacts obj) {
    LinkNode *pCur = start;
    LinkNode *pPre = nullptr;
    Contacts *removedData = nullptr;
    if (start == nullptr) throw "Invalid.";
    while (pCur) {
        if (pCur->data->getName() == obj.getName()) {
            if(pPre == nullptr) {
                start = pCur->next;
                if (start == nullptr) {
                    end = nullptr;
                }
            }
            else {
                pPre->next = pCur->next;
                if (pCur == end) {
                    end = pPre;
                }
            }

            removedData = pCur->data;
            delete pCur;
            count--;
            return *removedData;
        }

        pPre = pCur;
        pCur = pCur->next;
    }
    throw "Invalid";
}


Contacts& SinglyLinkedList::removeContact(int index) {
    Contacts* removedData;
    if (start == nullptr || index < 0 || index > count) throw "Invalid.";
    if (index == 0) {
        removedData = start->data;
        start = start->next;
        if (start == nullptr) {
            end = nullptr;
        }
        count--;
        return *removedData;
    }
    else {
        LinkNode *pCur = start;
        LinkNode *deleteNode = nullptr;
        for (int i = 0; i < index - 1; i++) {
            pCur = pCur->next;
        }
        deleteNode = pCur->next;
        pCur->next = deleteNode->next;
        removedData = deleteNode->data;
        delete deleteNode;
        if (pCur->next == nullptr) {
            end = pCur;
        }
        count--;
        return *removedData;
    }
}


int SinglyLinkedList::findContact(Contacts obj) const {
    LinkNode *pCur = start;
    int index = 0;
    
    while (pCur) {
        if (pCur->data->getName() == obj.getName()) {
            return index;
        }
        pCur = pCur->next;
        index++;
    }

    return -1;
}


Contacts SinglyLinkedList::getContact(int index) const {
    if (index < 0 || index > count) throw "Invalid";
    LinkNode *pCur = start;
    for (int i = 0; i < index; i++) {
        pCur = pCur->next;
    }

    return *(pCur->data);
}


void SinglyLinkedList::printList() const {
    LinkNode *pCur = start;
    int i = 1;
    while (pCur) {

        cout << "   "  << i << ". " << pCur->data->getName() << endl;
        
        i++;
        pCur = pCur->next;
    }
    if (i == 1) {
        cout << "No Contacts Available!\n";
    }
}

void SinglyLinkedList::replaceContact(Contacts oldContact, Contacts newContact) {
    LinkNode *pCur = start;

    while (pCur) {
        if (oldContact.getName() == pCur->data->getName() && oldContact.getPhone() == pCur->data->getPhone() && oldContact.getEmail() == pCur->data->getEmail() && oldContact.getAddress() == pCur->data->getAddress()) {
            pCur->data->setName(newContact.getName());
            pCur->data->setPhone(newContact.getPhone());
            pCur->data->setEmail(newContact.getEmail());
            pCur->data->setAddress(newContact.getAddress());
            return;
        }
        pCur = pCur->next;
    }
}

#endif