#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"

extern Node head;
Node *current;

int sendsig(char **args)
{
  int flag=0,numOfJobs,i;
  int jobnumber = atoi(args[1]);
  int signalnumber = atoi(args[2]);
  pid_t pidnumber;
  if(head.next!=NULL)
  {
    current = head.next;
    numOfJobs=1;
    while(current->next!=NULL)
    {
      numOfJobs++;
      current=current->next;
    }
    if(jobnumber > numOfJobs)
    {
      fprintf(stderr, "err: Invalid Job Number\n");
      return 1;
    }
    current=head.next;
    for(i=1; i!=numOfJobs-jobnumber+1;i++)
      current=current->next;
    pidnumber = current->pid;
    return kill(pidnumber, signalnumber)+1;
  }
  else
  {
      fprintf(stderr, "No Jobs To Kill\n");
  }
}
