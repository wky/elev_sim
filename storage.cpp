/*
storage.cpp
*/
#include <stdio.h>
#include "storage.h"

StorageManager::StorageManager(int init_vol){
    if (init_vol <= 0){
        // throw "WTF!";
        return;
    }
    head = new Passenger[init_vol];
#ifdef __DEBUG_STORAGE
    printf("__DEBUG_STORAGE: allocated #%d of Passengers.\n", init_vol);
#endif
    alloc = new AllocationNode;
    alloc->mem_ptr = head;
    alloc->mem_size = init_vol;
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
#ifdef __DEBUG_STORAGE
    printf("__DEBUG_STORAGE: given new Passenger at 0x%x.\n", ret);
#endif
    return ret;
}

void StorageManager::push_arrived(Passenger *p){
    if (p == NULL)
        return;
    p->next = NULL;
    tail->next = p;
    tail = p;
#ifdef __DEBUG_STORAGE
    printf("__DEBUG_STORAGE: reclaimed a Passenger at 0x%x.\n", tail);
#endif
}

void StorageManager::allocate_more(int amount){
    Passenger *new_mem = new Passenger[amount];
    alloc_tail->next = new AllocationNode;
    alloc_tail = alloc_tail->next;
    alloc_tail->mem_ptr = new_mem;
    alloc_tail->mem_size = amount;
    alloc_tail->next = NULL;
#ifdef __DEBUG_STORAGE
    printf("__DEBUG_STORAGE: allocated #%d more Passengers.\n", amount);
#endif
    head->next = new_mem;
    Passenger *mem_end = new_mem + amount - 1;
    for (; new_mem != mem_end; new_mem++)
        new_mem->next = new_mem + 1;
    mem_end->next = tail;
}

StorageManager::~StorageManager(){
    AllocationNode *ptr;
    while (alloc != NULL){
#ifdef __DEBUG_STORAGE
        printf("__DEBUG_STORAGE: delete #%d Passengers from 0x%x.\n", alloc->mem_size, alloc->mem_ptr);
#endif
        delete[] alloc->mem_ptr;
        ptr = alloc;
        alloc = alloc->next;
        delete ptr;
    }
}

