#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"
int PWDcommand(char **args)
{
	char buffer[PATH_MAX + 1];
	char *dir;
	dir = getcwd(buffer, PATH_MAX + 1);
	printf("%s\n", dir);
	return 1;
}
