#include<stdio.h>

typedef struct Student
{
int num;
char *name;
int age;
}Stu;

void menu()
{
printf("1.add\n");
printf("2.delete\n");
printf("3.show\n");
printf("4.find\n");
printf("0.exit\n");
}

int main()
{
int select=0;
do
{
menu();
printf("please enter your select:");
scanf("%d",&select);
switch(select)
{
case 1:

break;
}

}while()

return 0;
}
