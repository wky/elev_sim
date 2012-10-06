/*
   poisson.h 函数定义
*/
double poisson::poisson_function(int k);

poisson::poisson(ElevatorParameters* in_para)
{
	poisson_para = in_para;
	sum_area = 0; // 在一定的精度下取的区域个数
	for(; ; sum_area ++)
	{
		distribution[sum_area] = poisson_function(sum_area);
		if(distribution[sum_area] < pow(10*1.0, -5))
			break;
	}
}

double poisson::poisson_function(int k)
{
	double factorial = 1;

	for(int i = 1; i <= k; i ++) // 阶乘
		factorial = factorial*i;
	
	return pow(poisson_para.arrival_rate, k * 1.0) * pow(M_E, -poisson_para.arrival_rate) 
		/factorial; //泊松公式
}

int poisson::get_new()
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
}
