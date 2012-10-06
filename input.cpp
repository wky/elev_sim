/*
input.cpp
*/

#include "input.h"

void set_default(ElevatorParameters *param)
{
    param->elevator_num = 2;
    param->elevator_speed = 3;
    param->elevator_load = 7;
    param->level_num = 12;
    param->arrival_rate = 0.8;
    param->simulation_cycles = 200;
    param->algorithm_select = OperationAlgorithm.Default;
    param->output_file = default_output;
    param->verbose = false;
}

bool get_param(int argc, char *argv[], ElevatorParameters *param){
    if (param == NULL)
        return;
    set_default(param);
    int c;
    while ((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        int arg = atoi(optarg);
        switch (c) {
            case 'n':
                param->elevator_num = arg;
                break;
            case 's':
                param->elevator_speed = arg;
                break;
            case 'L':
                param->elevator_load = arg;
                break;
            case 'l':
                param->level_num = arg;
                break;
            case 'a':
                param->arrival_rate = atof(optarg);
                break;
            case 't':
                param->simulation_cycles = arg;
                break;
            case 'o':
                int len = strlen(optarg);
                param->output_file = new char[len+1];
                strcpy(param->output_file, optarg);
                break;
            case 'v':
                param->verbose = true;
                break;
            default:
                return false;
        }
    }
    if (param->elevator_num <= 0){
        fputs(elevator_num_error, stderr);
        return false;
    }
    if (param->elevator_speed <= 0){
        fputs(elevator_speed_error, stderr);
        return false;    
    }
    if (param->elevator_load <= 0){
        fputs(elevator_load_error, stderr);
        return false;
    }
    if (param->level_num <= 1){
        fputs(level_num_error, stderr);
        return false;    
    }
    if (param->arrival_rate <= 0){
        fputs(arrival_rate_error, stderr);
        return false;
    }
    if (param->simulation_cycles <= 0){
        fputs(simulation_cycles_error, stderr);
        return false;    
    }
    return true;
}
