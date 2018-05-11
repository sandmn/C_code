//使用main函数的参数，实现一个整数计算器，程序可以接受三个参数
////第一个参数“ - a”选项执行加法，“ - s”选项执行减法，“ - m”选项执行乘法，“ - d”选项执行除法
////后面两个参数为操作数。

#include<stdio.h>
////atoi函数：将字符串类型转换为整型，如果遇到非数字，则停止转换，返回整型数，否则返回0
////atoi(const char *arr)

int main(int argc, char*argv[], char*envp[])
{
	int a = atoi(argv[2]);//将字符串中的转化为整数，直到遇到非数字或‘\0’为止
	int b = atoi(argv[3]);
	if (argc != 4)
	{
	printf("please enter:%s,[-a|-s|-m|-d],data1,data2\n", argv[0]);
	return 1;
	}
	if (strcmp(argv[1], "-a") == 0)
	{
	printf("%d+%d=%d\n", a, b, a + b);
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
	printf("%d-%d=%d\n", a, b, a - b);
	}
	else if (strcmp(argv[1], "-m") == 0)
	{
	printf("%d*%d=%d\n", a, b, a * b);
	}
	else if (strcmp(argv[1], "-d") == 0)
	{
	if (b == 0)
	{	
	printf("div zero error!\n");
	return 2;
	}
	printf("%d/%d=%d\n", a, b, a / b);
	}
	else
	{
	printf("please enter:%s,[-a|-s|-m|-d],data1,data2\n", argv[0]);
	return 3;
	}

	return 0;
	}
