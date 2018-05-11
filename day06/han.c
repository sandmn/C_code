#include<stdio.h>
void hannuo(int n,char a,char b,char c)
{
	if(n==1)
	{
		printf("%c->%c\n",a,c);
	}
	else
	{
		hannuo(n-1,a,c,b);
		printf("%c->%c\n",a,c);
		hannuo(n-1,b,a,c);
	}
}

int main()
{
	hannuo(3,'A','B','C');
	printf("\n");
	return 0;
}
