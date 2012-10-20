
/*
logfile.h
记录状态
*/

#ifndef __logfile_h
#define __logfile_h

#include "defs.h"
#include <stdio.h>

//#define __DEBUG__LOG
//#define __verify
#define __show_stats

static char file_err[] = "Unable to open file.";

static unsigned int magic_num = 0x19951004;

static unsigned int data_offset = 100;

static unsigned int op_code[4] = {0, 1, 2, 0xff};  // 代码，表示 move, load, drop, end

class LogFile
{
    private:
        int levels;         // 层数
        int elevs;          // 电梯数
        FILE* fp;           // 要写入的文件
        int *new_pas;       // 数组记录新加的乘客
        int stats_pos;      // 文件中写入统计数据的位置
        int counter;        // 时间计数器
        int p_cnt;
        int total_wait;
        int total_onboard;
        int max_wait;
        int max_onboard;
        int total_dist;
        int total_run;      // 总行程
        int total_thput;    // 总运送量
#ifdef __verify
        int *pos;
        int *pas;
#endif
    public:
        LogFile(ElevatorParameters*);   // 构造函数，传入运行参数。默认电梯均处于1层
        ~LogFile();                     // 析构函数，释放资源
        void add(int, int);         // 记录新加乘客，参数分别是（楼层号，乘客数）
        void load(int, int);        // 记录电梯在当前楼层载客，传入（电梯号，乘客数）
        void drop(int, int);        // 记录乘客在当前楼层下电梯，传入（电梯号，乘客数）
        void move(int, int);        // 记录电梯移动，传入（电梯号，相对位移[向上为正]）
        void start_time_slot();     // 开始写该时间片的数据（新加乘客计算完后调用）
        void end_time_slot();       // 结束该时间片（电梯运行完后调用）
        void collect(Passenger&);
        void write_stats();         // 记录关于电梯的统计数据并写入文件
};

#endif

// signed-off-by: Weikun Yang wkyjyy@gmail.com


