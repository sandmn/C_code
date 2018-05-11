#include<stdio.h>

int fib(int n)
{
	int i;
		int ret=0;
	for(i=0;i<=n;i++)
	{
	ret +=i;
	}
	return ret;
	}


	int main()
	{
	int arr[10]={0,1};
	int i;
	for(i=2;i<10;i++)
	{
	arr[i]=arr[i-1]+arr[i-2];
	}
	printf("arr[9]=%d\n",arr[9]);

	printf("fib(9)=%d\n",fib(9));
	return 0;
	}
