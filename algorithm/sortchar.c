#include <stdio.h>
void sortchar()
{
	char a;
	scanf("%c", &a);
	if(a != '#')
	sortchar();
	if(a != '#')
	printf("%c",a);
}

int main()
{
	sortchar();
}
