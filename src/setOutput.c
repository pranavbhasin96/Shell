#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<errno.h>
#include "../mylib.h"

int setOutput(char **args, int tempout)
{
	int i=0;
	while(args[i]!=NULL)
	{
		if(strcmp(args[i],">")==0)
		{
			int fdout = open(args[i+1],O_RDWR|O_CREAT|O_TRUNC, 0777);
			dup2(fdout,1);
			close(fdout);
			return fdout;
		}
		if(strcmp(args[i],">>")==0)
		{
			int fdout = open(args[i+1],O_RDWR|O_APPEND|O_CREAT, 0777);
			dup2(fdout,1);
			close(fdout);
			return fdout;
		}
		i++;
	}
	int fdout = dup(tempout);
	dup2(fdout,1);
	return fdout;
}
