#include <stdio.h>

int binary_search(int a[], int n, int key)
{
	int mid;
	mid = n/2;
	if(a[mid] == key)
		return mid;
	if(a[mid] > key)
		return (binary_search(a, (n+1)/2, key));
	else if(a[mid] < key)
		return (binary_search(&a[mid], (n+1)/2, key));
		
} 

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9,10};
	printf("%d\n",binary_search(a, 10, 3));
	return 0;	
}
