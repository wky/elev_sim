#include "poisson.h"
#include "logfile.h"
#include "defs.h"
#include "levels.h"
#include <cstdlib>
#include <ctime>

Levels::Levels(ElevatorParameters& p, LogFile& l):pd(&p), logger(l){
    nl = p.level_num;
    go_up = vector<list<Passenger> >(nl);
    go_down = vector<list<Passenger> >(nl);
}

void Levels::generate_passenger(int time){
    for (int l = 0; l < nl; l++) {
        int newp = pd.get_next();
        logger.add(l, newp);
        while (newp--){
            Passenger p;
            p.arrival_time = time;
            p.arrival_level = l;
            p.destination_level = get_dest(l);
            if (p.destination_level > l)
                go_up[l].push_back(p);
            else
                go_down[l].push_back(p);
        }
    }
}

list<Passenger>& Levels::get_list(int l, bool up){
    if (up) return go_up[l];
    else return go_down[l];
}

int Levels::get_dest(int cur){
    int dest = rand()%(nl - 1);
    if (dest >= cur)
        dest++;
    return dest;
}

// signed-off-by: Weikun Yang wkyjyy@gmail.com
