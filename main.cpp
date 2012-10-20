#include "defs.h"
#include "levels.h"
#include "logfile.h"
#include "input.h"
#include "wmanager.h"
int main(int argc, char *argv[])
{
    ElevatorParameters p;
    get_param(argc, argv, &p);
    LogFile logger(&p);
    Levels levels(p, logger);
    WManager manager(p, levels, logger);
    manager.run();
    logger.write_stats();
    return 0;
}