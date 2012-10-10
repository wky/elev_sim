/*
log.h
记录状态
*/

#ifndef __LOG_H
#define __LOG_H

#include "defs.h"
#include <stdio.h>

static char file_err[] = "Unable to open file.";

class Log
{
    private:
        int levels;
        int elevs;
        FILE* fp;
    public:
        Log(ElevatorParameters*);   // 构造函数，传入运行参数。默认电梯均处于1层
        ~Log();                     // 析构函数，释放资源
        void add(int, int);         // 记录新加乘客，参数分别是（楼层号，乘客数）
        void load(int, int, int);        // 记录电梯在当前楼层载客，传入（楼层，电梯号，乘客数）
        void drop(int, int, int);        // 记录乘客在当前楼层下电梯，传入（楼层，电梯号，乘客数）
        void move(int, int, int);        // 记录电梯移动，传入（楼层，电梯号，相对位移[向上为正]）
};

#endif

