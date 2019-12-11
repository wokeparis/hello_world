#include <stdio.h>


int main()
{
	int i = 7;
	zigzag(7);
	
}

int zigzag(int n)
{
	int i,p;
	int num = 0;
	int j=0, k=0;
	int **a = (int **)malloc(n * 4);
	if(a == null)
		return 0;
	for(i = 0; i< n; i++)
	{
		a[i] = (int *)malloc(n * 4);
		if(a[i] == NULL)
		{
			while(--i >=0)
				free(a[i]);
			free(a);
			return 0;
		}
	}
	
	while(j != n&& k != n)
	{
		if((j+k)%2 == 1)//odd
		{
			if(j == n - 1 && k % 2 != 1)
				k++;
			if(k == 0)
				j++;
			else
			{
				j++;
				k--;
			}
		}
		else//even
		{
			if(k == n - 1 && j % 2 == 1)
				j++;
			if(j == 0)
				k++;
			else
			{
				j--;
				k++;				
			}
		}
		num++;
		a[j][k] = num;
		printf("%d\n",a[j][k]);
	}
	retutn 0;
}