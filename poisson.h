/*
   得到新的一批游客
 */

#ifndef _POISSON_
#define _POISSON_

#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include "defs.h"
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <ctime>

using namespace std;

class poisson
{
	public:
	poisson(ElevatorParameters*);
	double poisson_function(int k);
	int get_next();
	
	private:
	ElevatorParameters* poisson_para;
	double distribution[10000];
	int sum_area;
};

#endif 
