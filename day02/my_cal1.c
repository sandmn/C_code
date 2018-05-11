#include<stdio.h>
int isrun(int year)
{
return (year%4==0)&&(year%100!=0)||(year%400==0);
}


int main()
{
int a[2][13]={{0,31,28,31,30,31,30,31,31,30,31,31,31},
{0,31,29,31,30,31,30,31,31,30,31,31,31}};

int base_year=2000;
int base_month=1;
int base_week=6;

int input_year=0;
int input_month=0;

printf("please enter year/month:");
scanf("%d/%d",&input_year,&input_month);

int i=0;
int total=0;
for(i=base_year;i<input_year;i++)
{
total=total+365+isrun(i);
}

int year_week=(total+base_week)%7;
//printf("%d",year_week);
total=0;
for(i=1;i<input_month;i++)
{
total=total+a[isrun(input_year)][i];
}

int month_week=(year_week+total)%7;
printf("%d",month_week);

printf("Sun Mon Tue Wen Thr Fir Sar\n");
for(i=0;i<month_week;i++)
{
printf("    ");
}
for(i=1;i<=a[isrun(input_year)][input_month];i++)
{
printf("%3d ",i);
if((i+month_week)%7==0)
{
printf("\n");
}
}

printf("\n");
return 0;
}
