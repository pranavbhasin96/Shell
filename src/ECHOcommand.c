#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"
int ECHOcommand(char **args)
{
	int i;
	for(i=1; args[i]!=NULL; ++i)
	{
		printf("%s ",args[i]);
	}
	printf("\n");
	return 1;
}
