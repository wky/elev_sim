// TODO: add statistics part.

/*
storage.cpp
*/
#include <stdio.h>
#include <stdlib.h>
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
    total_dist = 0;
    total_onboard = 0;
    total_wait = 0;
    max_onboard = 0;
    max_wait = 0;
    p_cnt = 0;
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
#ifdef __DEBUG_STORAGE
    printf("__DEBUG_STORAGE: reclaimed a Passenger at 0x%x.\n", p);
#endif
    p_cnt++;
    total_dist += abs(p->destination_level - p->arrival_level);
    int t = p->in_time - p->arrival_time;
    total_wait += t;
    if (t > max_wait)
        max_wait = t;
    t = p->out_time - p->in_time;
    total_onboard += t;
    if (t > max_onboard)
        max_onboard = t;
    p->next = NULL;
    tail->next = p;
    tail = p;
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

void StorageManager::add_passenger_stats(Stats* stats){
    stats->avg_twait = (float)total_wait / p_cnt;
    stats->max_twait = (float)max_wait;
    stats->avg_tonboard = (float)total_onboard / p_cnt;
    stats->max_tonboard = (float)max_onboard;
    stats->avg_dist = (float)total_dist / p_cnt;
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

// signed-off-by: Weikun Yang wkyjyy@gmail.com

