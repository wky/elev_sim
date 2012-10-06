/*
   定义class evel_info中的函数
 */

#include "level_info.h"

level_info::level_info(ElevatorParameters* elev_para, StorageManager* level_manager)
:culculate_poisson(elev_para)
{
	transcript_elev = elev_para;                       // 问题定义的副本
	level_sto_manager = level_manager;                 // 后面调用其中的函数得到新的乘客连接到楼层乘客链表中
    pass_head = new Passenger*[transcript_elev->level_num];
    for(int i = 0; i < transcript_elev->level_num; i ++)
        pass_head[i] = new Passenger[1000];
    
	for(int i  = 0; i < transcript_elev->level_num; i ++)
	{
		pass_head[i]->next = NULL;
	}
}

void level_info::generate_passenger()              
{
	/*将新的乘客依次接到尾节点上*/
	int sum_next = culculate_poisson.get_next();    // 记录在泊松分布的计算下，该楼层得到的新乘客
	for(int i = 0; i < transcript_elev->level_num; i ++)
	{
		Passenger* tmp = pass_head[i];                        // 找到尾节点和插入新乘客的临时节点
		/*找到尾节点*/
		while(1)
		{   
			if(tmp->next == NULL)
				break;
			tmp = tmp->next;
	   	}

		int tmp_sumnext = sum_next*(1 - 0.5*(i/transcript_elev->level_num));//按照楼层修改新入的乘客数量
		for(int j = 0; j < tmp_sumnext; j ++)
		{
			tmp->next = level_sto_manager->get_new();
			tmp = tmp->next;
		}
		tmp->next = NULL;
	}
}

