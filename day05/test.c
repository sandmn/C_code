#include<stdio.h>
#include<stdlib.h>

void fun()
{
int *x=malloc(sizeof(int));
 x[10]=100;
}

int main()
{
fun();

printf("finish\n");
return 0;
}
