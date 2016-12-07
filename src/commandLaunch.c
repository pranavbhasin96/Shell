#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"

extern Node head;
extern pid_t fgpid;
extern char *fgname;

int commandLaunch(char **args)
{
	int i=0, flag = 0;
	pid_t pid;
	char strpid[15];
	int status;

	while(args[i]!=NULL)
	{
		if(strcmp(args[i],"&")==0)
		{
			args[i]=NULL;
			flag = 1;
			break;
		}
		i++;
	}

	pid = fork();
	//sprintf(strpid, "%d", pid);
	//printf("%s\n",strpid);
	if(pid == 0)
	{
		if(execvp(args[0],args) == -1)
		{
			perror("Child Process Failed");
		}
		exit(EXIT_FAILURE);
	}
	else if(pid < 0)
	{
		perror("Failed to fork");
	}
	else
	{
		if(flag == 0)
		{
			fgpid = pid;
			// strcpy(fgname, args[0]);
			fgname = args[0];
			// printf("%s", fgname);
			waitpid(pid, &status, WCONTINUED);
		}
		else
		{
			printf("%s [%d]\n", args[0], pid);

			Node * n = (Node *)malloc(sizeof(Node));
			n->pid = pid;
			strcpy(n->pname, args[0]);
			n->next = head.next;
			head.next = n;
		}
	}

	return 1;
}
