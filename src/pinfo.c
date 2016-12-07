#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<linux/limits.h>
#include<signal.h>
#include<errno.h>
#include "../mylib.h"
char pinfo(char ** params, char * basePath)
{
	char procPath[PATH_MAX + 1];
	strcpy(procPath, "/proc/");

	if(params[1])
		strcat(procPath, params[1]);
	else
		strcat(procPath, "self");

	char statPath[PATH_MAX + 1];
	strcpy(statPath, procPath);
	strcat(statPath, "/stat");

	errno = 0;
	FILE * stat = fopen(statPath, "r");
	if(stat < 0)
		perror("bash");

	int pid; char status; char name[20];
	char msg[100];
	fscanf(stat, "%d", &pid);
	fscanf(stat, "%s", name);
	fscanf(stat, " %c", &status);

	if(basePath == NULL)
		return status;

	//strcpy(msg, "pid: ");
	//strcat(msg, (pid));
	//write(2, msg, strlen(msg));
	fprintf(stdout, "pid: %d\n", pid);
	fprintf(stdout, "Process Status: %c\n", status);
	fclose(stat);

	errno = 0;
	strcpy(statPath, procPath); strcat(statPath, "/statm");
	FILE * mem = fopen(statPath, "r");
	if(mem < 0)
	{
		perror("bash");
	}
	int memSize; fscanf(mem, "%d", &memSize);
	fprintf(stdout, "Memory: %d\n", memSize);
	fclose(mem);

	char exePath[PATH_MAX + 1];
	strcpy(statPath, procPath);
	strcat(statPath, "/exe");
	errno = 0;

	readlink(statPath, exePath, sizeof(exePath));
	if(errno)
	{
		perror("bash");
	}

	char *ret;

	ret = strstr(exePath, basePath);
	int baseL = strlen(basePath);

	char relPath[PATH_MAX + 1];
	if(ret!=NULL)
	{
		relPath[0] = '~'; relPath[1] = '\0';
		strcat(relPath, (const char *)&exePath[baseL]);
	}
	else
	{
		strcpy(relPath, exePath);
		relPath[strlen(exePath)] = '\0';
	}

	int i = 0;
	while(exePath[i]) exePath[i++] = '\0';

	fprintf(stdout, "Executable Path: %s\n", relPath);
	return status;
}
