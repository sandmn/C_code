#include<stdio.h>
#define Black "\033[30m"
#define Red "\033[31m"
#define Green "\033[32m"
#define Yellow "\033[33m"
#define Blue "\033[34m"
#define YRed "\033[35m"
#define QGreen "\033[36m"
#define White "\033[37m"
int main()
{
	char buf[102]="#";
	char str[]="-/|\\";
	int i=0;
	for(i=1;i<=100;i++)
	{
		switch(i%8)
		{
			case 0:
				printf(Black);
				break;
			case 1:
				printf(Red);
				break;
			case 2:
				printf(Green);
				break;
			case 3:
				printf(Yellow);
				break;
			case 4:
				printf(Blue);
				break;
			case 5:
				printf(YRed);
				break;
			case 6:
				printf(QGreen);
				break;
			case 7:
				printf(White);
				break;
			default:
				break;
		}
		buf[i]='#';
		printf("[%-100s]\033[0m[%d%][%c]\r",buf,i,str[i%4]);
		fflush(stdout);
		usleep(100000);
	}
	printf("\n");
	return 0;
}
