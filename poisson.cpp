/*
   poisson.h 函数定义
*/

#include "poisson.h"
#include "defs.h"
#include <math.h>
#include <cmath>

poisson::poisson(ElevatorParameters* in_para)
{
	poisson_para = in_para;
}

double poisson::poisson_function(int k)
{
	double factorial = 1;

	for(int i = 1; i <= k; i ++) // 阶乘
		factorial = factorial*i;
	return pow((double)poisson_para->arrival_rate, k * 1.0)
            * pow(M_E*1.0, -poisson_para->arrival_rate*1.0)
            /factorial; //泊松公式
}
void poisson::culculate_dis()
{
    sum_area = 0; // 在一定的精度下取的区域个数
	for(; ; sum_area ++)
	{
		distribution[sum_area] = poisson_function(sum_area);
		if(distribution[sum_area] < 1e-5)
			break;
	}

}
int poisson::get_next()
{
	srand( (unsigned)time(0) ); // 以系统时间为种子
	double select_p = rand()/(double)(RAND_MAX); // 产生0~1的随即浮点数
	
	double P = 0; // 累计概率，使概率分布具有几何性质
	for(int i = 0; i < sum_area; i ++)
	{
		if(P > select_p)
			return i-1;
		P = P + distribution[i]; 
	}
    return sum_area;
}
