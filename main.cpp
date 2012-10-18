#include <stdio.h>
#include "storage.h"
#include "input.h"
#include "defs.h"
#include "level_info.h"
#include "manager.h"
#include "managerA.h"
#include "log.h"


int main(int argc, char *argv[])
{
    ElevatorParameters * param = new ElevatorParameters;
    bool input_res = get_param(argc, argv, param);
    if (!input_res)
        return 0;
    StorageManager * stom = new StorageManager();
    Log *log = new Log(param);
    level_info *levi = new level_info(param, stom, log);// 应该改(param, stom, log);
    // TODO: add algorithm selection
    manager* elevm = new managerA(param, levi, log); //应该改成managerA(param, levi, log);
    elevm->run();
    Stats* stats = new Stats;
    stom->add_passenger_stats(stats);
    log->write_stats(stats);
    delete log;
    delete levi;
    delete elevm;
    delete stats;
    delete stom;
    delete param;
    return 0;
    
}
// sob: Weikun "William" Yang wkyjyy@gmail.com
