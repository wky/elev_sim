/*
   定义class evel_info中的函数
 */

#include "level_info.h"
#include <math.h>

level_info::level_info(ElevatorParameters* elev_para, StorageManager* level_manager, Log* level_log)
:culculate_poisson(elev_para)
{
	transcript_elev = elev_para;                       // 问题定义的副本
	level_sto_manager = level_manager;                 // 后面调用其中的函数得到新的乘客连接到楼层乘客链表中
    passup_head = new Passenger*[transcript_elev->level_num];
    passup_tail = new Passenger*[transcript_elev->level_num];
    passdown_head = new Passenger*[transcript_elev->level_num];
    passdown_tail = new Passenger*[transcript_elev->level_num];
	for(int i  = 0; i < transcript_elev->level_num; i ++)
	{
        passup_head[i] = NULL;
		passup_tail[i] = NULL;
        passdown_head[i] = NULL;
		passdown_tail[i] = NULL;
	}
    
    updatelevel_log = level_log;
    //pierce_time = 0;
    srand( (unsigned)time(0) ); // 以系统时间为种子
}

void level_info::generate_passenger(int pierce_time)//传入时间点,每个时间片的开始处理一次
{
	/*将新的乘客依次接到尾节点上*/
	for(int i = 0; i < transcript_elev->level_num; i ++)
	{
        int sum_next = culculate_poisson.get_next();//记录在泊松分布的计算下，该楼层得到的新乘客
        updatelevel_log->add(i, sum_next); // 得到该楼层要得到的乘客，直接log记录要加的乘客数
        
#ifdef __DEBUG_LEVEL
        printf("adding #%d passengers on level #%d.\n", sum_next, i + 1);
#endif
        while (sum_next--)
        {
            /*先产生一个随机数得到目标楼层，然后初始化passenger*/
            Passenger* judge_tmp = level_sto_manager->get_new();
            int aim_level;
            while(1)
            {
                aim_level = rand() % (transcript_elev->level_num);
                if(aim_level != i)
                    break;
            }
            judge_tmp->arrival_time = pierce_time;
            judge_tmp->arrival_level = i;
            judge_tmp->destination_level = aim_level;
            printf("aim_level%d\n", aim_level);
            if(judge_tmp->destination_level - judge_tmp->arrival_level > 0)//上楼
            {
                if (passup_head[i] == NULL)
                {
                    passup_head[i] = judge_tmp;
                    passup_tail[i] = passup_head[i];
                }
                else
                {
                    passup_tail[i]->next = judge_tmp;
                    passup_tail[i] = passup_tail[i]->next;
                }
            }
            
            else//下楼
            {
                if (passdown_head[i] == NULL)
                {
                    passdown_head[i] = judge_tmp;
                    passdown_tail[i] = passdown_head[i];
                }
                else
                {
                    passdown_tail[i]->next = judge_tmp;
                    passdown_tail[i] = passdown_tail[i]->next;
                }
            }
            
            
        }
	}
    
}

