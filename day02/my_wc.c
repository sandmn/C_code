#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		fprintf(stderr,"please enter:%s,file\n,",argv[0]);
		exit(1);
	}

	FILE *fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		fprintf(stderr,"open of %s error",argv[1]);
		exit(1);
	}

	fseek(fp,0,SEEK_END);
	long ls=ftell(fp);
	rewind(fp);

	char *buf=(char*)malloc(ls);
	if(buf==NULL)
	{
		fprintf(stderr,"error malloc\n");
		exit(1);
	}


	int l=0;
	int c=0;
	int w=0;
	int flag=0;
	fread(buf,1,ls,fp);
	int i=0;
	for(i=0;i<ls;i++)
	{
		c++;
		if(buf[i]=='\n')
		{
			l++;
		}
		//if(isspace(buf[i]))
		//{
		//	w++;
		//}
		if(flag==0&&(!isspace(buf[i])))
		{
			w++;
			flag=1;
		}
		else if(isspace(buf[i]))
		{
			flag=0;
		}
	}

	printf("character:%d,line:%d,word:%d\n",c,l,w);
	free(buf);
	buf=NULL;

	fclose(fp);
	return 0;
}
