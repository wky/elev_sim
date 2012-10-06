#include <stdio.h>
#include "storage.h"
#include "input.h"
#include "defs.h"
#include "level_info.h"
#include "poisson.h"

int main(int argc, char *argv[])
{
    ElevatorParameters * param = new ElevatorParameters;
    bool input_res = get_param(argc, argv, param);
    if (!input_res)
        return 0;
    StorageManager * m = new StorageManager();
    level_info *levels = new level_info(param, m);
    //levels->generate_passenger();
    return 0;
    
}
// sob: Weikun "William" Yang wkyjyy@gmail.com
