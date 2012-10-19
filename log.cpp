// TODO: add statistics calculations.

/*
log.cpp
Log类
*/

#include <stdlib.h>
#include "log.h"

Log::Log(ElevatorParameters* param){
    levels = param->level_num;
    elevs = param->elevator_num;
    total_thput = 0;
    total_run = 0;
    fp = fopen(param->output_file,"wb");    //二进制写
    if (fp == NULL){
        perror(file_err);
        exit(EXIT_FAILURE);
    }
    counter = 0;
    //文件头魔数
    fwrite((void*)&magic_num, sizeof(unsigned int), 1, fp);
    //版本号
    fwrite((void*)&version_code, sizeof(unsigned int), 1, fp);
    //运行参数的前7个变量
    fwrite((void*)param, sizeof(int) * 6 + sizeof(float), 1, fp);
    //预留统计数据的位置
    stats_pos = ftell(fp);
    //填充0xff直到data_offset
    for (int i = ~0; ftell(fp) < data_offset;)
        fwrite((void*)&i, sizeof(int), 1, fp);
    new_pas = new int[levels];
}

Log::~Log(){
    fflush(fp);
    fclose(fp);
    delete[] new_pas;
}

void Log::add(int level, int num)
{
    new_pas[level] = num;
#ifdef __DEBUG__LOG
    printf("add %d to level %d\n", num, level);
#endif
}

void Log::load(int elev_id, int num)
{
    // 记录电梯载客
    fwrite((void*)(op_code + 1), sizeof(int), 1, fp);
    fwrite((void*)&elev_id, sizeof(int), 1, fp);
    fwrite((void*)&num, sizeof(int), 1, fp);
#ifdef __DEBUG__LOG
    printf("load %d from elev %d\n", num, elev_id);
#endif
}

void Log::drop(int elev_id, int num)
{
    // 记录电梯下客
    fwrite((void*)(op_code + 2), sizeof(int), 1, fp);
    fwrite((void*)&elev_id, sizeof(int), 1, fp);
    fwrite((void*)&num, sizeof(int), 1, fp);
#ifdef __DEBUG__LOG
    printf("drop %d from elev %d\n", num, elev_id);
#endif
    total_thput += num;
}

void Log::move(int elev_id, int diff)
{
    // 记录电梯移动
    fwrite((void*)op_code, sizeof(int), 1, fp);
    fwrite((void*)&elev_id, sizeof(int), 1, fp);
    fwrite((void*)&diff, sizeof(int), 1, fp);
#ifdef __DEBUG__LOG
    printf("move %d elev %d\n", diff, elev_id);
#endif
    total_run += abs(diff);
}

void Log::start_time_slot(){
    // 写入时间戳
    fwrite((void*)&counter, sizeof(int), 1, fp);
    counter++;
    // 写入新加的乘客
    fwrite((void*)new_pas, sizeof(int), levels, fp);
}

void Log::end_time_slot(){
    // 记录该时间片结束
    fwrite((void*)(op_code + 3), sizeof(int), 1, fp);
}

void Log::write_stats(Stats* stats){
    stats->avg_thput = (float)total_thput / counter;
    stats->avg_run100 = (float)total_run / elevs / total_thput * 100;
    fseek(fp, stats_pos, 0);
    fwrite((void*)stats, sizeof(Stats), 1, fp);
}

// signed-off-by: Weikun Yang wkyjyy@gmail.com

