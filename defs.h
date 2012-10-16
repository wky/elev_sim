/*
defs.h
定义
*/

#ifndef __defs_h
#define __defs_h

static unsigned int version_code = 0x1;
/*
调度算法选择
*/
enum OperationAlgorithm
{
    Default = 1,
    ManagerA = 1,
    ManagerB
};

/*
运行参数
*/
struct ElevatorParameters
{
    int elevator_num;       //电梯数量
    int elevator_speed;     //电梯速度(一个时间片内)
    int elevator_load;      //电梯载客量
    int level_num;          //楼层数量
    float arrival_rate;    //乘客到达数量(时间片内平均)
    int simulation_cycles;  //模拟循环数(时间片)
    OperationAlgorithm algorithm_select;  //调度算法选择
    char *output_file;      //输出的文件名
    bool verbose;           //是否输出细节
};

/*
乘客信息
*/
struct Passenger
{
    int arrival_time;       //到达时间
    int arrival_level;      //到达层数
    int destination_level;  //目标层数
    int in_time;            //入梯时间
    int out_time;           //出梯时间
    Passenger *next;        //单链表指针
};

/*
统计数据
*/
struct Stats
{
    float avg_twait;       //平均等待时间
    float max_twait;       //最长等待时间
    float avg_tonboard;    //平均乘梯时间
    float max_tonboard;    //最长乘梯时间
    float avg_thput;       //平均运送率（单位时间内运达数量）
    float max_thput;       //最高运送率
    float avg_load;        //平均载客量（电梯内的人数）
    float avg_dist;        //平均楼层差（乘客的目的层数减出现层数）
    float avg_run100;      //平均电梯行程（每百位乘客）
};

#endif

// signed-off-by: Weikun Yang wkyjyy@gmail.com


