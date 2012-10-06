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
	double poisson_function(int k); // 构造泊松公式，计算有限个点的概率
	int get_next(); // 由得到的泊松分布，产生随即数，确定新乘客的个数
	
	private:
	ElevatorParameters* poisson_para;
	double distribution[10000];
	int sum_area;
};

#endif 
