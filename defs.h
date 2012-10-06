/*
defs.h
定义
*/

#ifndef __defs_h
#define __defs_h

/*
调度算法选择
*/
enum OperationAlgorithm{
    ManagerA,
    ManagerB
}

/*
运行参数
*/
struct ElevatorParameters{
    int elevator_num;       //电梯数量
    int elevator_speed;     //电梯速度(一个时间片内)
    int elevator_load;      //电梯载客量
    int level_num;          //楼层数量
    double arrival_rate;    //乘客到达数量(时间片内平均)
    int simulation_cycles;  //模拟循环数(时间片)
    enum algorithm_select;  //调度算法选择
}

/*
乘客信息
*/
struct Passenger{
    int arrival_time;       //到达时间
    int arrival_level;      //到达层数
    int destination_level;  //目标层数
    int waiting_time;       //等待时间(不含梯内时间)
    Passenger *next;        //单链表指针
}

#endif
