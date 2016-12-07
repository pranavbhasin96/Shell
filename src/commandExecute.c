#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"
int commandExecute(char **commandSegregated, char *initialDir)
{
	if(commandSegregated[0]==NULL)
		return 1;

	if(strcmp(commandSegregated[0], "cd")==0)
		return CDcommand(commandSegregated, initialDir);
	else if(strcmp(commandSegregated[0], "pwd")==0)
		return PWDcommand(commandSegregated);
	else if(strcmp(commandSegregated[0], "exit")==0 || strcmp(commandSegregated[0],"quit")==0)
		return EXITcommand();
	else if(strcmp(commandSegregated[0], "echo")==0)
		return ECHOcommand(commandSegregated);
	else if(strcmp(commandSegregated[0], "pinfo")==0)
	{
		pinfo(commandSegregated, initialDir);
		return 1;
	}
	else if(strcmp(commandSegregated[0], "listjobs")==0)
	{
		listjobs();
		return 1;
	}
	else if(strcmp(commandSegregated[0], "sendsig")==0)
		return sendsig(commandSegregated);
	else if(strcmp(commandSegregated[0], "killallbg")==0)
		return killallbg();
	else if(strcmp(commandSegregated[0],"fg")==0)
		return fg(commandSegregated);

	return commandLaunch(commandSegregated);
}
