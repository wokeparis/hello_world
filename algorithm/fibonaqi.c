#include <stdio.h>
int fibonaqi(int n)
{
	if(n == 0)
	return 0;
	else if(n == 1)
	return 1;
	else
	return fibonaqi(n - 1) + fibonaqi(n - 2);
}
int main()
{
	printf("the rabbit is %d", fibonaqi(10));
}
