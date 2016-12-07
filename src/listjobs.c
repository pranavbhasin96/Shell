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
Node *current;
void listjobs()
{
  int numOfJobs = 1000,i,j;
  char **joblist = malloc(numOfJobs*sizeof(char*));
  pid_t pidlist[1000];

  if(!joblist)
  {
    fprintf(stderr, "bash: allocation error!");
    exit(EXIT_FAILURE);
  }

  if(head.next!=NULL)
  {
    i=0;
    current = head.next;
    joblist[i]=current->pname;
    pidlist[i]=current->pid;
    i++;
    while(current->next!=NULL)
    {
      current=current->next;
      joblist[i] = current->pname;
      pidlist[i] = current->pid;
      i++;
    }
    for(j = i-1; j >=0 ; --j)
    {
      printf("[%d] %s [%d]\n", i-j, joblist[j], pidlist[j]);
    }
    return;
  }
  else
    return;
}
