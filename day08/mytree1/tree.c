#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
void print_tree(const char *str,int num,char c)
{
	DIR *dp_str = opendir(str);
	if(dp_str == NULL)
	{
		fprintf(stderr,"error:open of direction(%s)\n",str);
		exit(1);
	}
	
	struct dirent* dp = NULL;
	while((dp = readdir(dp_str)) != NULL)
	{
		if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0)
		{
			continue;
		}

		int i=0;
		for(i=0;i<num;i++)
		{
			printf("%c",c);
		}

		printf("%s\n",dp->d_name);
//		char *p = strrchr(tmp,'/');
//		if(p == NULL)
//		{
//			printf("%s\n",tmp);
//		}
//		else
//		{
//			printf("%s\n",p+1);
//		}


		int len = strlen(str) + strlen(dp->d_name) + 2;
		char *tmp = malloc(len);
		if(tmp == NULL)
		{
			fprintf(stderr,"error malloc\n");
			exit(1);
		}
		sprintf(tmp,"%s/%s",str,dp->d_name);
		

		struct stat sbuf_str;
		lstat(tmp,&sbuf_str);

		if(S_ISDIR(sbuf_str.st_mode))
		{
			print_tree(tmp,num+4,c);
		}

		free(tmp);
	}


	closedir(dp_str);
}

int main()
{
	print_tree(".",4,'-');
	return 0;
}
