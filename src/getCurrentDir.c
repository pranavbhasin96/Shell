#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"

char *getCurrentDir(char *initialDir)
{
	char *currWorkDir, *token;
	char buffer[PATH_MAX + 1];
	char *directory;
	size_t length;
	char *home = "~";

	currWorkDir = getcwd(buffer, PATH_MAX + 1 );
	if(strcmp(currWorkDir, initialDir)==0)
		return home;

	token = strrchr(currWorkDir, '/');

	if( currWorkDir == NULL ){
		printf("bash: Error");
		exit(1);
	}

	if (token == NULL) {
		printf("bash: Error");
		exit(1);
	}

	length = strlen(token);
	directory = malloc(length);
	memcpy(directory, token+1, length);

	return directory;
}
