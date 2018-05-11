#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{

if(argc != 3)
{
printf("Please enter:%s src dst\n",argv[0]);
return 0;
}

int ret=0;
FILE *src=fopen(argv[1],"rb");
if(src == NULL)
{
ret=1;
goto end;
}

FILE *dst=fopen(argv[2],"wb");
if(dst == NULL)
{
ret=2;
goto end;
}

fseek(src,0,SEEK_END);
long lsize=ftell(src);
rewind(src);

char *buf=(char *)malloc(lsize);
if(buf == NULL)
{
ret=3;
goto end;
}
fread(buf,1,lsize,src);
fwrite(buf,1,lsize,dst);


end:
if(ret!=0)
{
perror("");
return 1;
}
if(src!=NULL)
{
fclose(src);
}
if(dst!=NULL)
{
fclose(dst);
}
if(buf!=NULL)
{
free(buf);
buf=NULL;
}
return 0;


}
