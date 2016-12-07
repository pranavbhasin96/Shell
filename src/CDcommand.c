#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"

int CDcommand(char **args, char *initialDir)
{
	if(args[1]==NULL)
	{
		chdir(initialDir);
	}
	else
	{
		if(chdir(args[1]) != 0)
		{
			perror("bash");
		}
	}
	return 1;
}
