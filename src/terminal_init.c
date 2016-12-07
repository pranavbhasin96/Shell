#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"
#define MAX_LENGTH 1000

extern Node head;
extern pid_t fgpid;
extern char *fgname;
Node * lead, * follow;

void handler(int signum)
{
	pid_t proc_id;
	int   status;
	(proc_id = waitpid(-1, &status, WNOHANG));
	if (proc_id>0)
	{
		if(head.next != NULL)
			follow = head.next;

		if(follow->next != NULL && follow->pid != proc_id)
		{
			lead = follow->next;

			while(lead != NULL)
			{
				if(lead->pid == proc_id)
				{
					printf("%s [%d] %d\n", lead->pname, proc_id,WEXITSTATUS(status));
					follow->next = lead->next;
					free(lead);
					break;
				}
				else
				{
					follow = lead;
					lead = follow->next;
				}
			}
			return;
		}

		else if(follow->pid == proc_id)
		{
			printf("%s [%d] %d\n", follow->pname, proc_id,WEXITSTATUS(status));
			head.next = follow->next;
			free(follow);
			return;
		}

	}
	return;
}

void stop_handler(int signum)
{
	kill(fgpid, 20);
	Node * n = (Node *)malloc(sizeof(Node));
	n->pid = fgpid;
	strcpy(n->pname, fgname);
	n->next = head.next;
	head.next = n;
	kill(fgpid, 18);
}

void c_handler(int signum)
{
	return;
}

void terminal_init()
{
	int flag;
	char hostname[100],username[100], **commandInput, **commandSegregated, buffer[PATH_MAX + 1], **commandSegregatedByPipe;
	gethostname(hostname, sizeof(hostname));
	getlogin_r(username,sizeof(username));
	char *initialDir = getcwd(buffer, PATH_MAX + 1);
	do{
		// printf("%d",fgpid);
		signal(SIGTSTP, stop_handler);
		signal(SIGINT, c_handler);
		int i,j,k,numOfPiped;
		char line[MAX_LENGTH];
		ssize_t bufsize = 0;
		char *dir = getCurrentDir(initialDir);
		printf("<%s@%s: %s > ",username,hostname,dir);

		if(!gets(line,MAX_LENGTH,stdin))
		{
			// printf("\n");
			exit(1);
		}
		commandInput = split(line, ";");
		for(i= 0; commandInput[i]!=NULL; ++i)
		{
			int tempin=dup(0);
			int tempout=dup(1);
			commandSegregatedByPipe = split(commandInput[i],"|");
			numOfPiped=0;
			while(commandSegregatedByPipe[numOfPiped]!=NULL)
			{
				numOfPiped++;
			}
			if(numOfPiped==1)
			{
				commandSegregated = split(commandSegregatedByPipe[0], " \t\n\r\a");
				setOutput(commandSegregated, tempout);
				setInput(commandSegregated, tempin);
				j=0;
				while(commandSegregated[j]!=NULL && strcmp(commandSegregated[j],"<")!=0 && strcmp(commandSegregated[j],">")!=0 && strcmp(commandSegregated[j],">>")!=0)
					j++;
				if(commandSegregated[j]!=NULL)
					commandSegregated[j]=NULL;
				flag = commandExecute(commandSegregated, initialDir);
				signal(SIGCHLD, handler);
				dup2(tempin,0);
				dup2(tempout,1);
				close(tempin);
				close(tempout);
				if(flag == 0)
					break;
			}
			else
			{
				int in,fd[2];
				for(j = 0; j < numOfPiped - 1; ++j)
				{
					commandSegregated = split(commandSegregatedByPipe[i], " \t\r\n\a");
					if(j==0)
					{
						setInput(commandSegregated, tempin);
						k=0;
						while(commandSegregated[k]!=NULL && strcmp(commandSegregated[k],"<")!=0)
							k++;
						if(commandSegregated[k]!=NULL)
							commandSegregated[k]=NULL;
					}

					pipe(fd);
					if(j!=0)
						dup2(in,0);
					dup2(fd[1],1);
					flag = commandExecute(commandSegregated, initialDir);
					signal(SIGCHLD,handler);
					close(fd[1]);
					in = fd[0];
				}

				commandSegregated = split(commandSegregatedByPipe[j], " \t\r\n\a");
				setOutput(commandSegregated, tempout);
				k=0;
				while(commandSegregated[k]!=NULL && strcmp(commandSegregated[k],">")!=0 && strcmp(commandSegregated[k],">>")!=0)
					k++;
				if(commandSegregated[k]!=NULL)
					commandSegregated[k]=NULL;
				dup2(in,0);
				flag = commandExecute(commandSegregated, initialDir);
				signal(SIGCHLD, handler);
				dup2(tempin,0);
				dup2(tempout,1);
				close(tempin);
				close(tempout);
				if(flag==0)
				break;
			}
		}
	}while(flag);
}
