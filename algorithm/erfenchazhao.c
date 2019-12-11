#include <stdio.h>

int binary_search(int a[], int n, int key)
{
	int mid, l = 0, r = n-1;
	while(l < r - 1)
	{
		mid = (l+r)/2;
		
		if(a[mid] < key)
			l = mid +1;
		else if(a[mid] > key)
			r = mid - 1;
		else
			return mid; 
	}
	if(a[l] == n)
		return l;
	else if(a[r] == n)
		return r;
	else 
		return -1;
		
} 

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10};
	printf("%d\n",binary_search(a, 10, 2));
	return 0;	
}
