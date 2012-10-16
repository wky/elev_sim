//
//  manager.h
//  
//
//  Created by Siyumato on 12-10-10.
//
//
/*manager*/
#ifndef _manager_h
#define _manager_h

#include "defs.h"
#include "level_info.h"
#include "log.h"
/*电梯策略的基类*/

//只是用level_info 来进行上乘和下乘的操作
//在一格manager对象里对所有的电梯进行操作
class manager
{
private:
    ElevatorParameters* ManaElev_para;
    int *direction;                  //当前电梯运行方向(1为上，-1为下，如果到达1或者n，反号)
    Passenger** head;                //电梯上的乘客头
    Passenger** tail;                //电梯上的乘客尾
    /*从head->next开始存放passenger*/
    int *level;
    int *sum_passenger;
    Log* write_log;
    level_info* levelInfo_forManager;//楼层信息
    int now_time;//当前的时间片
    
public:
    manager(){}
    virtual void manage(){}
    ~manager(){}
};

#endif
