/*
class Levels
*/

#ifndef __levels_h
#define __levels_h

#include "poisson.h"
#include "defs.h"
#include "logfile.h"
#include <vector>
#include <list>

class Levels {
private:
    poisson pd;
    LogFile& logger;
    int nl;
    int get_dest(int);
public:
    std::vector<std::list<Passenger> > go_up;
    std::vector<std::list<Passenger> > go_down;
    Levels(ElevatorParameters& , LogFile&);
    std::list<Passenger>& get_list(int, bool);
    void generate_passenger(int);
};

#endif