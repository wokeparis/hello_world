#include <stdio.h>

int fun(int a)
{
	if(a == 1)
		return 1;
	else 
		return 2*fun(a-1)+1;
}
int main()
{
	printf("%d", fun(3));
}
