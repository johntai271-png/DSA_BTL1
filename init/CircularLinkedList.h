#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "IList.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

template<class T>
class CircularLinkedList : public IList<T> {
public:
    class Node;

protected:
    Node* head;
    Node* tail;
    int count;
    bool (*itemEqual)(T& lhs, T& rhs);
    void (*deleteUserData)(CircularLinkedList<T>*);

public:
    CircularLinkedList(
        void (*deleteUserData)(CircularLinkedList<T>*) = 0,
        bool (*itemEqual)(T&, T&) = 0
    )
        : head(nullptr), tail(nullptr), count(0),
          itemEqual(itemEqual), deleteUserData(deleteUserData) {}

    CircularLinkedList(const CircularLinkedList<T>& list)
        : head(nullptr), tail(nullptr), count(0),
          itemEqual(list.itemEqual), deleteUserData(list.deleteUserData) {
        copyFrom(list);
    }

    CircularLinkedList<T>& operator=(const CircularLinkedList<T>& list) {
        if (this == &list) return *this;
        removeInternalData();
        itemEqual = list.itemEqual;
        deleteUserData = list.deleteUserData;
        copyFrom(list);
        return *this;
    }

    ~CircularLinkedList() {
        removeInternalData();
    }

    void add(T e) override {
        // TODO Q2
        Node*newnode=new Node(e);
        if(count==0){
            head=newnode;
            tail=newnode;
            newnode->next=newnode;
            count++;
            return;
        }
        tail->next=newnode;
        newnode->next=head;
        tail=newnode;
        count++;
        return;
    }

    void add(int index, T e) override {
        // TODO Q2
    if(index<0||index>count) throw std::out_of_range("Index is out of range!");
        Node*newnode=new Node(e);    
    if(index==0){
        if(count==0){
            head=tail=newnode;
            newnode->next=newnode;
            count++;
            return;
        }
            newnode->next=head;
            tail->next=newnode;
            head=newnode;
            count++;
            return;
        }
        Node*cur=head;
        for(int i=0;i<index-1;i++){
            cur=cur->next;
        }
        newnode->next=cur->next;
        cur->next=newnode;
        cur=newnode;
    if(cur->next==head){
            tail=cur;
        }
        count++;
    }

    T removeAt(int index) override {
        // TODO Q2
    if(index<0||index>=count) throw std::out_of_range("Index is out of range!");
    Node*temp=nullptr;
    T removedData;
    if(index==0){
        temp=head;
        removedData=temp->data;
        head=head->next;
        tail->next=head;
        delete temp;
        count--;
        return removedData;
    }
    Node*cur=head;
    for(int i=0;i<index-1;i++){
        cur=cur->next;
    }
    temp=cur->next;
    removedData=temp->data;
    cur->next=temp->next;
    if(cur->next==head){
        tail=cur;
    }
    delete temp;
    count--;
    return removedData;
}

    bool removeItem(T item, void (*removeItemData)(T) = 0) override {
    
    
        // TODO Q2
    Node*cur=head;
        for(int i=0;i<count;i++){
            if(equals(cur->data,item,itemEqual)){
               T removedData=removeAt(i);
              if(removeItemData!=nullptr){
                removeItemData(removedData);
              }
              return true;  
            }
            cur=cur->next;
        }
       return false; 
    }

    void clear() override {
        // TODO Q2
    removeInternalData();
    head=nullptr;
    tail=nullptr;
    count=0;
    }

    T& get(int index) override {
        // TODO Q2
    if (index < 0 || index >= count) throw std::out_of_range("Index is out of range!");
    Node*cur=head;
    for(int i=0;i<index;i++){
        cur=cur->next;
    }
    return cur->data;
}

    int indexOf(T item) override {
        // TODO Q2
    Node*cur=head;
    for(int i=0;i<count;i++){
        if(equals(cur->data,item,itemEqual)){
            return i;
        }
        cur=cur->next;
    }
    return -1;
    }

    bool empty() override { return count == 0; }
    int size() override { return count; }
    bool contains(T item) override { return indexOf(item) >= 0; }

    string toString(string (*item2str)(T&) = 0) override {
        stringstream ss;
        ss << "[";
        Node* cur = head;
        for (int i = 0; i < count; ++i) {
            if (i > 0) ss << ", ";
            if (item2str) ss << item2str(cur->data);
            else ss << cur->data;
            cur = cur->next;
        }
        ss << "]";
        return ss.str();
    }

    void println(string (*item2str)(T&) = 0) {
        cout << toString(item2str) << endl;
    }

protected:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T&)) {
        return itemEqual ? itemEqual(lhs, rhs) : (lhs == rhs);
    }

    void copyFrom(const CircularLinkedList<T>& list) {
        Node* cur = list.head;
        for (int i = 0; i < list.count; ++i) {
            add(cur->data);
            cur = cur->next;
        }
    }

    void removeInternalData() {
        if (deleteUserData != 0) deleteUserData(this);
        Node* cur = head;
        for (int i = 0; i < count; ++i) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        count = 0;
    }

public:
    class Node {
    public:
        T data;
        Node* next;
        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };
};

#endif
