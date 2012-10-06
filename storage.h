/*
storage.h
管理乘客的存储
*/
#ifndef __storage_h
#define __storage_h

/*
StorageManager类
单链表的内存池管理乘客
*/

class StorageManager{
    private:
        Passenger *head;
        Passenger *tail;
        void allocate_more(int amount = 50);
    public:
        StorageManager(int init_vol = 512);
        Passenger* get_new();               //获取新乘客(数据未初始化)
        void push_arrived(Passenger *);     //回退到达后的乘客并统计信息
        ~StorageManager();
}

#endif

