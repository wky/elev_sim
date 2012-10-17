//
//  managerA.h
//  
//
//  Created by Siyumato on 12-10-10.
//
//
/*manager 的 派生类*/
#ifndef _managerA_h
#define _managerA_h

#include "defs.h"
#include "level_info.h"
#include "manager.h"
#include "log.h"

class managerA:public manager
{
public:
    managerA(ElevatorParameters*, level_info*, Log*);
    void manage();
    void run();
    ~managerA();
};

#endif
