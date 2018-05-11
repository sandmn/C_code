#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
void copy_file(const char *src,const char *dst,mode_t md_src)
{
//	struct stat sbuf_dst;
//	lstat(dst,&sbuf_dst);
//	sbuf_dst.st_mode = md_src;

	chmod(dst,md_src);

	FILE* fp_src = fopen(src,"r");
	if(fp_src == NULL)
	{
		fprintf(stderr,"error of open %s\n",src);
		exit(1);
	}

	FILE* fp_dst = fopen(dst,"w");
	if(fp_dst == NULL)
	{
		fprintf(stderr,"error of open %s\n",dst);
		exit(1);
	}
	
	char buf[4096];
	int r;
	while((r = fread(buf,1,sizeof(buf),fp_src)) > 0)
	{
		fwrite(buf,1,r,fp_dst);
	}
	fclose(fp_src);
	fclose(fp_dst);
}

void copy_dir(const char *src,const char *dst)
{
	DIR *dp_src = opendir(src);
	if(dp_src == NULL)
	{
		fprintf(stderr,"the open of %s error\n",src);
		exit(1);
	}
	struct dirent *dp = NULL;

	struct stat sbuf_src;
	while((dp = readdir(dp_src)) != NULL)
	{
		if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0)
		{
			continue;
		}
		
		int len_src = strlen(src) + strlen(dp->d_name) + 2;
		char *tmp_src = malloc(len_src);
		if(tmp_src == NULL)
		{
			fprintf(stderr,"malloc error\n");
			exit(1);
		}
		memset(tmp_src,0x00,len_src);
		sprintf(tmp_src,"%s/%s",src,dp->d_name);
		lstat(tmp_src,&sbuf_src);//question
		if(S_ISREG(sbuf_src.st_mode))
		{
			int len = strlen(dp->d_name) + strlen(dst) + 2;
			char *tmp = malloc(len);
			if(tmp == NULL)
			{
				fprintf(stderr,"error malloc\n");
				exit(1);
			}
			sprintf(tmp,"%s/%s",dst,dp->d_name);
			copy_file(tmp_src,tmp,sbuf_src.st_mode);
			free(tmp);
		}
		else if(S_ISDIR(sbuf_src.st_mode))
		{

			int len = strlen(dp->d_name) + strlen(dst) + 2;
			char *tmp = malloc(len);
			if(tmp == NULL)
			{
				fprintf(stderr,"error malloc\n");
				exit(1);
			}
			sprintf(tmp,"%s/%s",dst,dp->d_name);
			mkdir(tmp,sbuf_src.st_mode);
			copy_dir(tmp_src,tmp);
			free(tmp);
		}
		free(tmp_src);
	}
	closedir(dp_src);
}

int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr,"please enter:%s src dst\n",argv[0]);
		exit(1);
	}

	struct stat sbuf_src;
	lstat(argv[1],&sbuf_src);

	if(lstat(argv[1],&sbuf_src) == -1)
	{
		fprintf(stderr,"the %s not exist\n",argv[1]);
		exit(1);
	}

	int old = umask(0);

	struct stat sbuf_dst;
	lstat(argv[2],&sbuf_dst);
	if(S_ISREG(sbuf_src.st_mode))
	{
		if(lstat(argv[2],&sbuf_dst) == -1)
		{
			copy_file(argv[1],argv[2],sbuf_src.st_mode);
		}
		else if(S_ISREG(sbuf_dst.st_mode))
		{

			char c = 'n';
			printf("cover the %s?[y|n]",argv[2]);
			scanf("%[yYnN]",&c);
			if(c == 'y' || c == 'Y')
			{
				copy_file(argv[1],argv[2],sbuf_src.st_mode);		
			}
		}
		else if(S_ISDIR(sbuf_dst.st_mode))
		{
			int len = strlen(argv[1]) + strlen(argv[2]) + 2;
			char *tmp = malloc(len);
			if(tmp == NULL)
			{
				printf("error of malloc!\n");
				exit(1);
			}
			memset(tmp,0x00,len);
			sprintf(tmp,"%s/%s",argv[2],argv[1]);
			copy_file(argv[1],tmp,sbuf_src.st_mode);
			free(tmp);
		}
	}
	else if(S_ISDIR(sbuf_src.st_mode))
	{
		if(lstat(argv[2],&sbuf_dst) == -1)
		{
			mkdir(argv[2],sbuf_src.st_mode);
			copy_dir(argv[1],argv[2]);
		}
		else if(S_ISDIR(sbuf_dst.st_mode))
		{
			int len = strlen(argv[1]) + strlen(argv[2]) + 2;	
			char *tmp = malloc(len);
			if(tmp == NULL)
			{
				printf("error1 of malloc!\n");
				exit(1);
			}
			memset(tmp,0x00,len);
			sprintf(tmp,"%s/%s",argv[2],argv[1]);
			mkdir(tmp,sbuf_src.st_mode);
			copy_dir(argv[1],tmp);
			free(tmp);
		}
		else 
		{
			fprintf(stderr,"not copy direction to file\n");
			exit(1);
		}
	}
	umask(old);
	return 0;
}
