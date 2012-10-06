/*
storage.cpp
*/
#include "storage.h"

StorageManager::StorageManager(int init_vol){
    if (init_vol <= 0){
        // throw "WTF!";
        return;
    }
    head = new Passenger[init_vol];
    alloc = new AllocationNode;
    alloc->mem_ptr = head;
    alloc->next = NULL;
    alloc_tail = alloc;
    tail = head + (init_vol - 1);
    for (Passenger *ptr = head; ptr != tail; ptr++)
        ptr->next = ptr + 1;
    tail->next = NULL;
}

Passenger* StorageManager::get_new(){
    Passenger *ret = head;
    if (head->next == tail)
        allocate_more();
    head = head->next;
    ret->next = NULL;
    return ret;
}

void StorageManager::push_arrived(Passenger *p){
    if (p == NULL)
        return;
    p->next = NULL;
    tail->next = p;
    tail = p;
}

void StorageManager::allocate_more(int amount){
    Passenger *new_mem = new Passneger[amount];
    head->next = new_mem;
    new_mem->next = tail;
    alloc_tail->next = new AllocationNode;
    alloc_tail = alloc_tail->next;
    alloc_tail->mem_ptr = new_mem;
    alloc_tail->next = NULL;
}

StorageManager::~StorageManager(){
    AllocationNode *ptr;
    while (alloc != NULL){
        delete[] alloc->mem_ptr;
        ptr = alloc;
        alloc = alloc->next;
        delete ptr;
    }
}

