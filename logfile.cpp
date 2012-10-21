
/*
fogfile.cpp
LogFile类
*/

#include <stdlib.h>
#include "logfile.h"

LogFile::LogFile(ElevatorParameters* param){
    levels = param->level_num;
    elevs = param->elevator_num;
    p_cnt = 0;
    total_wait = 0;
    total_onboard = 0;
    max_wait = 0;
    max_onboard = 0;
    total_dist = 0;
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
#ifdef __verify
    pos = new int[elevs];
    pas = new int[levels];
    for (int i = 0; i < levels; i++)
        pas[i] = 0;
#endif
}

LogFile::~LogFile(){
    fflush(fp);
    fclose(fp);
    //delete []new_pas;
}

void LogFile::add(int level, int num)
{
    new_pas[level] = num;
#ifdef __verify
    pas[level] += num;
    printf("L%d : %d\n", level, pas[level]);
#endif
#ifdef __DEBUG__LOG
    printf("add %d to level %d\n", num, level);
#endif
}

void LogFile::collect(Passenger& p){
    p_cnt ++;
    int dist = abs(p.destination_level - p.arrival_level);
    total_dist += abs(p.destination_level - p.arrival_level);
    int t = p.in_time - p.arrival_time;
    total_wait += t;
    if (t > max_wait)
        max_wait = t;
#ifdef  __show_stats
    printf("collect%d\n",p_cnt);
    printf("dist:%d wait:%d\n",dist,t);
#endif
    t = p.out_time - p.in_time;
    total_onboard += t;
    if (t > max_onboard)
        max_onboard = t;
#ifdef  __show_stats
    printf("onboard: %d\n",t);
#endif
}

void LogFile::load(int elev_id, int num)
{
    // 记录电梯载客
    fwrite((void*)(op_code + 1), sizeof(int), 1, fp);
    fwrite((void*)&elev_id, sizeof(int), 1, fp);
    fwrite((void*)&num, sizeof(int), 1, fp);
#ifdef __DEBUG__LOG
    printf("load %d from elev %d\n", num, elev_id);
#endif
#ifdef __verify
    pas[pos[elev_id]] -= num;
    printf("mod L%d : %d\n", pos[elev_id], pas[pos[elev_id]]);
    if (pas[pos[elev_id]] < 0)
        printf("oh no!! ---\n");
#endif
}

void LogFile::drop(int elev_id, int num)
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

void LogFile::move(int elev_id, int diff)
{
    // 记录电梯移动
    fwrite((void*)op_code, sizeof(int), 1, fp);
    fwrite((void*)&elev_id, sizeof(int), 1, fp);
    fwrite((void*)&diff, sizeof(int), 1, fp);
#ifdef __DEBUG__LOG
    printf("move %d elev %d\n", diff, elev_id);
#endif
    total_run += abs(diff);
#ifdef __verify
    pos[elev_id] += diff;
#endif 
}

void LogFile::start_time_slot(){
    // 写入时间戳
    fwrite((void*)&counter, sizeof(int), 1, fp);
    counter++;
    // 写入新加的乘客
    fwrite((void*)new_pas, sizeof(int), levels, fp);
}

void LogFile::end_time_slot(){
    // 记录该时间片结束
    fwrite((void*)(op_code + 3), sizeof(int), 1, fp);
}

void LogFile::write_stats(){
    Stats stats;
    stats.avg_twait = (float)total_wait / p_cnt;
    stats.max_twait = (float)max_wait;
    stats.avg_tonboard = (float)total_onboard / p_cnt;
    stats.max_tonboard = (float)max_onboard;
    stats.avg_dist = (float)total_dist / p_cnt;
    stats.avg_thput = (float)total_thput / counter;
    stats.avg_run100 = (float)total_run / elevs / total_thput * 100;
    printf("avg waiting time:%f\nmax waiting time:%f\n",
           stats.avg_twait, stats.max_twait);
    printf("avg onboard time:%f\nmax onboard time:%f\n",
           stats.avg_tonboard, stats.max_tonboard);
    printf("avg distance:%f\navg throughput:%f\navg runing per 100:%f\n",
           stats.avg_dist, stats.avg_thput, stats.avg_run100);
    fseek(fp, stats_pos, 0);
    fwrite((void*)&stats, sizeof(Stats), 1, fp);
}

// signed-off-by: Weikun Yang wkyjyy@gmail.com

