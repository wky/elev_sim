//
//  managerA.cpp
//  
//
//  Created by Siyumato on 12-10-10.
//
//
#include "managerA.h"
#include "defs.h"
#include "level_info.h"
#include "manager.h"
#include "log.h"

managerA::managerA(ElevatorParameters* elev_para ,level_info* levinfo, Log* manalog)
{
    write_log = manalog;
    levelInfo_forManager = levinfo;
    ManaElev_para = elev_para;
    direction = new int[elev_para->elevator_num+1];
    level = new int[elev_para->elevator_num+1];
    sum_passenger = new int[elev_para->elevator_num+1];
    head = new Passenger*[elev_para->elevator_num+1];
    tail = new Passenger*[elev_para->elevator_num+1];
    for(int i = 0; i < elev_para->elevator_num+1; i ++)
    {
        direction[i] = 1; // 初始情况下假设在1层向上运动
        head[i] = new Passenger;
        tail[i] = head[i];
        sum_passenger[i] = 0;
    }
    now_time = 0;
}

void managerA::manage()
{/*每操作一次manage  
    *先改变电梯方向
    第一步：查看有没有下乘的
    第二步：查看有没有上乘的
    第三步：查看电梯里有没有人
    第四步：改变相应的manager的变量，层数（由改变以后的方向运行一次manage就改变一层）
            log前面三步
  */
    for(int num_elev = 0; num_elev < ManaElev_para->elevator_num; num_elev ++)
    {
        int sum_on = 0;//记录在这一个电梯的当前位置下，上乘了的乘客数；
        int sum_off = 0;//记录在这一个电梯的当前位置下，下乘了的乘客数；
        
        if(level[num_elev] == 1 || level[num_elev] == ManaElev_para->level_num)
            direction[num_elev] = -direction[num_elev];
        
        Passenger* checkpre = head[num_elev]->next;
        Passenger* checkrear = head[num_elev];
        /*第一步*/
        while(checkpre != NULL)
        {
            if(sum_passenger[num_elev] == 0) break;
            else if( (checkpre->destination_level-checkpre->arrival_level)
                    * direction[num_elev] > 0)//说明是同方向的
            {
                sum_off ++;
                sum_passenger[num_elev] --;
                // push_arrived 该乘客
                checkrear->next = checkpre->next;//把这个乘客去掉
                (levelInfo_forManager->level_sto_manager)->push_arrived(checkpre);
                checkpre = checkrear->next;
            }
            else
            {
                checkrear = checkpre;//把这个乘客去掉
                checkpre = checkpre->next;
            }
        }
        
        /*第二步*/
        while(1)//不断上乘
        {
            if(sum_passenger[num_elev] == ManaElev_para->elevator_load)//满载
                break;
            if(direction[num_elev] == 1)//上行
            {
                Passenger* pullp = levelInfo_forManager->passup_head[level[num_elev]];
                if(pullp != NULL)//说明该层有人要上行
                {
                    tail[num_elev]->next = pullp;
                    levelInfo_forManager->passup_head[level[num_elev]] = pullp->next;
                    sum_passenger[num_elev] ++;
                    sum_on ++;
                    pullp->out_time = now_time;//记录乘客的出梯时间
                }
                else break;//上行无人
            }
            else
            {
                Passenger* pullp = levelInfo_forManager->passdown_head[level[num_elev]];
                if(pullp != NULL)//说明该层有人要上行
                {
                    tail[num_elev]->next = pullp;
                    levelInfo_forManager->passdown_head[level[num_elev]] = pullp->next;
                    sum_passenger[num_elev] ++;
                    sum_on ++;
                    pullp->out_time = now_time;//记录乘客的出梯时间
                }
                else break;//下行无人
            }
        }
        
        /*第三步，判断电梯是否移动*/
        write_log->load(num_elev, sum_on);
        write_log->drop(num_elev, sum_off);
        if(sum_passenger[num_elev] != 0)
        {
            level[num_elev] += direction[num_elev];
            write_log->move(num_elev, direction[num_elev]);
        }
        else
            write_log->move(num_elev,0);
    }
}

void managerA::run()
{
    /*
     第一层循环：时间片的循环
        修改level_info
        第二层循环：以速度为单位的循环
            运行楼层，如果中间需要停止等待，直接结束这个循环
     */
    for(int pierce = 0; pierce < ManaElev_para->simulation_cycles; pierce ++)
    {
        write_log->start_time_slot();
        levelInfo_forManager->generate_passenger(pierce);
        for(int go = 0; go < ManaElev_para->elevator_speed; go ++)
        {
            manage();
        }
        write_log->end_time_slot();
    }
}

managerA::~managerA()
{
    delete []direction;
    delete []level;
    delete []sum_passenger;
    for(int i = 0; i < ManaElev_para->elevator_num; i ++)
    {
        delete []head[i];
    }
    delete []head;
    delete []tail;
}
