#include <stdio.h>
#include "storage.h"
#include "input.h"
#include "defs.h"
int main(int argc, char *argv[])
{
	int a=0;
    int b = 1;
    printf("yeah, it works!\n%d\n", a+b);
    
    ElevatorParameters * param = new ElevatorParameters;
    bool input_res = get_param(argc, argv, param);
    if (!input_res)
        return 0;
    printf("param: %d,%d,%d,%d,%lf,%d,%s,%d,%s\n",
           param->elevator_num,
           param->elevator_speed,
           param->elevator_load,
           param->level_num,
           param->arrival_rate,
           param->simulation_cycles,
           param->output_file,
           param->algorithm_select,
           param->verbose?"yes":"no");
    return 0;
}


// sob: Weikun "William" Yang wkyjyy@gmail.com

