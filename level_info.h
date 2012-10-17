/*
   生成当前楼层乘客状态
 */

#ifndef _LEVEL_INFO
#define _LEVEL_INFO

#include <iostream>
#include <stdio.h>
#include "defs.h"
#include "storage.h"
#include "poisson.h"
#include "log.h"
#include <math.h>

//#define __DEBUG_LEVEL

using namespace std;

class level_info
{
	public:
	level_info(ElevatorParameters* , StorageManager*, Log*);       // 使用定义初始化楼层信息
	void generate_passenger(int);                               // 在一个时间片以后将得到的新乘客连入列表
	
	ElevatorParameters* transcript_elev;                     // 定义中变量的副本
	Passenger** passup_head; 	                                 // 楼层乘客的链表
	Passenger** passup_tail;
    Passenger** passdown_head; 	                                 // 楼层乘客的链表
	Passenger** passdown_tail;
    StorageManager* level_sto_manager;                      // 后面调用其中的函数得到新的乘客连接到楼层乘客链表中
	poisson culculate_poisson;
    Log* updatelevel_log;//每层新加乘客的记录
    //int pierce_time;
};

#endif
