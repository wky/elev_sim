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
    pass_tail = new Passenger*[transcript_elev->level_num];
	for(int i  = 0; i < transcript_elev->level_num; i ++)
	{
        pass_head[i] = NULL;
		pass_tail[i] = NULL;
	}
}

void level_info::generate_passenger()              
{
	/*将新的乘客依次接到尾节点上*/
	for(int i = 0; i < transcript_elev->level_num; i ++)
	{
        int sum_next = culculate_poisson.get_next();//记录在泊松分布的计算下，该楼层得到的新乘客
#ifdef __DEBUG_LEVEL
        printf("adding #%d passengers on level #%d.\n", sum_next, i + 1);
#endif
        while (sum_next--) {
            if (pass_head[i] == NULL){
                pass_head[i] = level_sto_manager->get_new();
                pass_tail[i] = pass_head[i];
            }
            else{
                pass_tail[i]->next = level_sto_manager->get_new();
                pass_tail[i] = pass_tail[i]->next;
            }
        }
	}
}

