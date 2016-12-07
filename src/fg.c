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
Node *lead, *follow, *current;

int fg(char **args)
{
	int numOfJobs,status;
  int jobnumber = atoi(args[1]);
  int i;
  pid_t pidnumber;
  if(head.next!=NULL)
  {
    current = head.next;
    numOfJobs = 1;
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
    follow=head.next;
    lead = follow->next;
    if(jobnumber == numOfJobs)
    {
      pidnumber = follow->pid;
      head.next = follow->next;
      free(follow);
      waitpid(pidnumber, &status, WCONTINUED);
      return 1;
    }
    else
    {
      for(i=1; i!=numOfJobs-jobnumber;i++)
      {
        follow = follow->next;
        lead = follow->next;
      }
      pidnumber = lead->pid;
      follow->next = lead->next;
      free(lead);
      waitpid(pidnumber, &status, WCONTINUED);
      return 1;
    }
  }
  else
  {
    fprintf(stderr, "err: Invalid Background Number\n");
    return 1;
  }

}
