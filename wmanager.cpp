#include "wmanager.h"
#include <algorithm>
WManager::WManager(ElevatorParameters& p, Levels& levels, LogFile& logfile):
lm(levels),
logger(logfile),
onboard(p.elevator_num),
position(p.elevator_num, 0),
direc(p.elevator_num)
{
    numE = p.elevator_num; 
    maxload = p.elevator_load;
    numL = p.level_num;
    speed = p.elevator_speed;
    simCycle = p.simulation_cycles;
}

void WManager::run(){
    for (cnt = 0; cnt < simCycle; cnt++){
        lm.generate_passenger(cnt);
        logger.start_time_slot();
        for (int e = 0; e < numE; e++)
            manage(e);
        logger.end_time_slot();    
    }

}

void WManager::manage(int id){
    int moves = 0;
    int op_cnt = 0;
    while (moves < speed){
        op_cnt++;
        int out_cnt = 0;
        list<Passenger>::iterator it = onboard[id].begin();
        list<Passenger>::iterator it_d;
        while (it != onboard[id].end()){
            it_d = it;
            it++;
            Passenger p = *it_d;
            if (p.destination_level == position[id]){
                p.out_time = cnt + moves? 1: 0;
                logger.collect(p);
                out_cnt++;
                onboard[id].erase(it_d);
            }
        }
        if (out_cnt)
            logger.drop(id, out_cnt);
        
        if (position[id] == 0)
            direc[id] = true; // go up
        else if (position[id] == numL - 1)
            direc[id] = false; // go down

        std::list<Passenger>& wait_same = lm.get_list(position[id], direc[id]);
        std::list<Passenger>& wait_not_same = lm.get_list(position[id], !direc[id]);
        if (onboard[id].empty() && wait_same.empty() && !wait_not_same.empty()){ // try reverse
            direc[id].flip();
            load(id, wait_not_same);
        }else
            load(id, wait_same);//lm.get_list(position[id], direc[id]));

        if (onboard[id].size() || needs_to_go(id, direc[id])){
            position[id] += direc[id]? 1 : -1;
            /*
            if (position[id] < 0 || position[id] >= numL){
                char str[5];
                str[0]='0';
                printf("wtfwtfwtf!!!");
            }*/
            logger.move(id, direc[id]? 1 : -1);
            moves++;
        }
        else if (needs_to_go(id, !direc[id])){
            direc[id].flip();
            position[id] += direc[id]? 1 : -1;
            /*
            if (position[id] < 0 || position[id] >= numL){
                char str[5];
                str[0]='0';
                printf("wtf!");
            }*/
            logger.move(id, direc[id]? 1 : -1);
            moves++;
        }
        else break;
    }
}

void WManager::load(int id, list<Passenger>& waiting){
    int in_cnt = 0;
    list<Passenger>::iterator it = waiting.begin();
    list<Passenger>::iterator it_d;
    while (onboard[id].size() < maxload && it != waiting.end()){
        it_d = it;
        it++;
        Passenger p = *it_d;
        p.in_time = cnt;
        onboard[id].push_back(p);
        in_cnt++;
        waiting.erase(it_d);
    }
    if (in_cnt){
        logger.load(id, in_cnt);
#ifdef __verify
        printf("in lm: L%d, %d\n",
               position[id],
               lm.go_up[position[id]].size() + 
               lm.go_down[position[id]].size());
#endif
    }
}

bool WManager::needs_to_go(int id, bool test_dir){
    int l = position[id];
    if (test_dir) l++;
    else l--;
    while (l >= 0 && l < numL){
        if (!lm.get_list(l, true).empty() || !lm.get_list(l, false).empty()) // test on both directions.
            return true;
        if (test_dir) l++;
        else l--;
    }
    return false;
}
