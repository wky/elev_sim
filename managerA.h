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
#include "log.h"

class managerA:public manager
{
public:
    managerA(ElevatorParameters*);
    void manage();
    void run();
    ~manager();
};

#endif
