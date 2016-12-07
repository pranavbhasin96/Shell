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

int killallbg()
{
  if(head.next!=NULL)
  {
    int returnval = 1;
    current=head.next;
    while(current!=NULL)
    {
      returnval*=(kill(current->pid, 9) + 1);
      current=current->next;
    }
    return returnval;
  }
  else
    return 1;
}
