#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"usage:%s,filename\n",argv[0]);
		exit(1);
	}

	FILE *fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		fprintf(stderr,"the %s not exists\n",argv[1]);
		exit(1);
	}
	
	char buf[4096];
	int r = 0;
	while((r = fread(buf,1,sizeof(buf),fp)) > 0)
	{
		printf("%d\n",r);
	}
	printf("eof = %d\n",feof(fp));	
	
	printf("error = %d\n",ferror(fp));	
	fclose(fp);
}
