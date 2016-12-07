#ifndef __MYLIB_H__
#define __MYLIB_H__

#include<stdio.h>

char pinfo(char **, char *);
int PWDcommand(char **);
char **split(char *, char *);
void terminal_init();
int CDcommand(char **, char *);
int commandExecute(char **, char *);
void handler(int);
int commandLaunch(char **);
int EXITcommand();
int ECHOcommand(char **);
char *getCurrentDir(char *);
int setInput(char **, int);
int setOutput(char **, int);
void listjobs();
int sendsig(char **);
int killallbg();
int fg(char **);

typedef struct Node
{
  pid_t pid;
  char *pname;
  struct Node *next;
}Node;

#endif
