#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../mylib.h"

int setInput(char **args, int tempin)
{
	int i=0;
	while(args[i]!=NULL)
	{
		if(strcmp(args[i],"<")==0)
		{
			int fdin = open(args[i+1],O_RDWR, 0777);
			dup2(fdin,0);
			close(fdin);
			return fdin;
		}
		i++;
	}
	int fdin = dup(tempin);
	dup2(fdin,0);
	return fdin;
}
