/*
   生成当前楼层乘客状态
 */

#ifndef _LEVEL_INFO
#define _LEVEL_INFO

#include <iostream>
#include <stdio.h>
#include "defs.h"
#include "storage.h"
#include "poisson"

using namespace std;

class level_info
{
	public:
	level_info(ElevatorParameters* , StorageManager*);         // 使用定义初始化楼层信息
	void generate_passager();                // 在一个时间片以后将得到的新乘客连入列表
	
	ElevatorParameters* transcript_elev;     // 楼层对定义中变量的副本
	Passenger* pass_head; 	                 // 每层楼乘客的链表
	StorageManager* level_stomanger;         // 后面调用其中的函数得到新的乘客连接到楼层乘客链表中
	poisson culculate_poisson;
};

#endif
