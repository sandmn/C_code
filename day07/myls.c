#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<string.h>
void show_mode(mode_t md)
{
	char mode[12]="?---------.";
	if((md & S_IFMT) == S_IFSOCK) mode[0]='s'; 
	if((md & S_IFMT) == S_IFLNK) mode[0]='l';
	if((md & S_IFMT) == S_IFDIR) mode[0]='d';
	if((md & S_IFMT) == S_IFBLK) mode[0]='b';
	if((md & S_IFMT) == S_IFCHR) mode[0]='c';
	if((md & S_IFMT) == S_IFREG) mode[0]='-';
	if((md & S_IFMT) == S_IFIFO) mode[0]='p';


	if(md & S_IRUSR) mode[1]='r';
	if(md & S_IWUSR) mode[2]='w';
	if(md & S_IXUSR) mode[3]='x';

	if(md & S_IRGRP) mode[4]='r';
	if(md & S_IWGRP) mode[5]='w';
	if(md & S_IXGRP) mode[6]='x';

	if(md & S_IROTH) mode[7]='r';
	if(md & S_IWOTH) mode[8]='w';
	if(md & S_IXOTH) mode[9]='x';

	printf("%s ",mode);
}
void show_color(mode_t mode)
{
	if(S_ISDIR(mode))
	{
		printf("\033[1;34m");
	}
	else if(S_ISLNK(mode)) 
	{
		printf("\033[1;36m");
	}
	else if(S_ISCHR(mode))
	{
		printf("\033[1;33;40m");
	}
	else if(S_ISBLK(mode))
	{
		printf("\033[1;33;40m");
	}
	else if(S_ISFIFO(mode))
	{
		printf("\033[33;40m");
	}
}
int total = 0;

void show(const char * file)
{
	struct stat fbuf;
	lstat(file,&fbuf);

	if(lstat(file,&fbuf) == -1)
	{
		printf("not have this file\n");
		exit(1);
	}


	show_mode(fbuf.st_mode);

	printf("%d ",fbuf.st_nlink);
	
	struct passwd *u = getpwuid(fbuf.st_uid);
	if(u != NULL)
	{	
		printf("%s ",u->pw_name);
	}

	struct group *g = getgrgid(fbuf.st_gid);
	if(g != NULL)
	{
		printf("%s ",g->gr_name);
	}

	printf("%d ",fbuf.st_size);

	struct tm *t = localtime(&fbuf.st_mtime);
	if(t != NULL)
	{
		printf("%04d-%02d%02d ",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
		printf("%02d:%02d:%02d ",t->tm_hour,t->tm_min,t->tm_sec);
	}

	show_color(fbuf.st_mode);
	char *p = strrchr(file,'/');

	
	if(p == NULL)
	{
		printf("%s ",file);
	}
	else
	{
		printf("%s ",p+1);
	}
	printf("\033[0m");
	if(S_ISLNK(fbuf.st_mode))
	{
		printf("-> ");
		char yf[256];
		readlink(file,yf,sizeof(yf));
		printf("%s ",yf);
	}
}


int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"please enter:%s,filename\n",argv[0]);
		exit(1);
	}

	struct stat sbuf;
	lstat(argv[1],&sbuf);

	if(lstat(argv[1],&sbuf) == -1)
	{
		printf("not have this file\n");
		return 1;
	}
	if(S_ISDIR(sbuf.st_mode))
	{
		

		DIR *dp=opendir(argv[1]);

		if(dp == NULL)
		{
			perror("openfir error\n");
			return 2;
		}
		


		struct dirent *d;

		while(d = readdir(dp))
		{
			if(strcmp(d->d_name,".") == 0 || strcmp(d->d_name,"..") == 0)
			{
				continue;
			}
			int len = strlen(d->d_name) + strlen(argv[1]) + 2;
			char *file = malloc(len);
			if(file == NULL)
			{
				printf("malloc error\n");
				exit(1);
			}
			memset(file,0x00,len);
			sprintf(file,"%s/%s",argv[1],d->d_name);

			struct stat sbuf_file;
			lstat(file,&sbuf_file);
			total += sbuf_file.st_size;
		}
		closedir(dp);
		printf("total %d\n",total);

		dp =opendir(argv[1]);
		while(d = readdir(dp))
		{
			if(d->d_name[0]=='.')
			{
				continue;
			}
		//	char file[500];//need change
			int len = strlen(argv[1]) + strlen(d->d_name) + 2;
			char *file = malloc(len);
			if(file == NULL)
			{
				fprintf(stderr,"malloc error\n");
				exit(1);
			}
			memset(file,0x00,len);
			sprintf(file,"%s/%s",argv[1],d->d_name);
			show(file);
			printf("\n");
		}
		closedir(dp);
	}
	else
	{
		
		show(argv[1]);
	}

	printf("\n");
	return 0;
}
