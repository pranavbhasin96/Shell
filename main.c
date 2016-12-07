#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "mylib.h"

Node head;
pid_t fgpid;
char *fgname;

int main()
{
	head.next = NULL;
	terminal_init();
	return EXIT_SUCCESS;
}
