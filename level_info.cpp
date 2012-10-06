/*
   定义class evel_info中的函数
 */

#include "level_info.h"

level_info::level_info(ElevatorParameters* elev_para, StorageManager* level_manager)
{
	transcript_elev = elev_para;                       // 问题定义的副本
	level_sto_manager = level_manager;                 // 后面调用其中的函数得到新的乘客连接到楼层乘客链表中
	culculate_poisson = new poisson(transcript_elev);
}

void level_info::generate_passenger()              
{
	Passenger* tmp = pass_head;                        // 找到尾节点和插入新乘客的临时节点
	/*找到尾节点*/
	while(1)
	{
		if(tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	/*将新的乘客依次接到尾节点上*/
	for(int i = 0; i < culculate_poisson.get_next(); i ++)
	{
		tmp->next = level_sto_manager.get_new();
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

