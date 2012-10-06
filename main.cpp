#include <stdio.h>
#include "storage.h"
#include "input.h"
#include "defs.h"
int main()
{
    int a=0;
    int b = 1;
    printf("yeah, it works!\n%d\n", a+b);
/*
    StorageManager * m = new StorageManager(5);
    Passenger* ptr = m->get_new();
    printf("m:0x%x, ptr:0x%x\n", m, ptr);
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    m->push_arrived(ptr);
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    m->push_arrived(ptr);
    ptr = m->get_new();
    printf("ptr:0x%x\n", ptr);    
    m->push_arrived(ptr);
    delete m;
*/    
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