/*
    class WManager
*/

#ifndef __wmanager_h
#define __wmanager_h

#include "defs.h"
#include "levels.h"
#include "logfile.h"

#include <list>
#include <vector>

//#ifndef __verify
//#define __verify
//#endif

class WManager {
private:
    Levels lm;
    LogFile logger;
    int numE;
    int numL;
    int maxload;
    int speed;
    int simCycle;
    int cnt;
    std::vector<int> position;
    std::vector<std::list<Passenger> > onboard;
    std::vector<bool> direc;
    void manage(int);
    bool needs_to_go(int, bool);
    void load(int, std::list<Passenger>&);
public:
    WManager(ElevatorParameters&, Levels&, LogFile&);
    void run();
};
#endif

// signed-off-by: Weikun Yang wkyjyy@gmail.com
