// TODO: add statistics part.

/*
storage.h
管理乘客的存储
*/
#ifndef __storage_h
#define __storage_h

#include "defs.h"

#define __DEBUG_STORAGE


/*
 AllocationNode类
 形成记录内存分配的链表
 */
struct AllocationNode{
    Passenger *mem_ptr;
    int mem_size;
    AllocationNode *next;
};

/*
StorageManager类
单链表的内存池管理乘客
*/

class StorageManager{
    private:
        Passenger *head;
        Passenger *tail;
        AllocationNode *alloc;
        AllocationNode *alloc_tail;
        void allocate_more(int amount = 100);
        int p_cnt;
        int total_wait;
        int total_onboard;
        int total_thput;
        int total_dist;
        int max_wait;
        int max_onboard;
        int max_thput;
    public:
        StorageManager(int init_vol = 512);
        Passenger* get_new();               // 获取新乘客(数据未初始化，next ptr是NULL)
        void push_arrived(Passenger *);     // 回退到达后的乘客并统计信息
        void add_passenger_stats(Stats*);   // 写入关于乘客的统计信息
        ~StorageManager();
};

#endif




