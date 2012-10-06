/*
input.h
处理命令行参数
函数:
    void get_param(int, char*[], ElevatorParameters*);
*/
#ifndef __input_h
#define __input_h

#include <getopt.h>
#include <string.h>
#include "defs.h"

static char simulation_cycles_error[] = "cycles of simulation must be greater than 0!\n";
static char elevator_num_error[] =      "number of elevators must be greater than 0!\n";
static char elevator_speed_error[] =    "speed of elevators must be greater than 0!\n";
static char elevator_load_error[] =     "load of elevators must be greater than 0!\n";
static char level_num_error[] =         "number of levels must be greater than 1!\n";
static char arrival_rate_error[] =      "rate of arrival must be greater than 0!\n";

static char default_output[] = "output";

static char short_opt[] = "n:s:L:l:a:t:o:v";
static option long_opt[] = {
    {"verbose",     no_argument,       NULL, 'v'},
    {"elevators",   required_argument, NULL, 'n'},
    {"speed",       required_argument, NULL, 's'},
    {"load",        required_argument, NULL, 'L'},
    {"levels",      required_argument, NULL, 'l'},
    {"rate",        required_argument, NULL, 'a'},
    {"time",        required_argument, NULL, 't'},
    {"output",      required_argument, NULL, 'o'},
    {NULL,          0,                 NULL,  0}
};

bool get_param(int, char *[], ElevatorParameters *);

#endif

