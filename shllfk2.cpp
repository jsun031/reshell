#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#define MAXLINE 80
using namespace std;

void setup(char inputBuffer[], char *argv[])
{
	char *p;
	int i,j;
	i=0;
	for (p=inputBuffer;;p++)
	{
		argv[i++]=p;
		while(*p!=' '&& *p!='\0')
			p++;
		if(*p=='\0')
			break;
		*p='\0';
	}
	argv[i]=NULL;
	int pid;
	pid=fork();
	if (pid==0)
	{
		execvp(argv[0],argv);
		printf("command not found\n");
	}
	else if(pid>0)
		wait(NULL);
	else
	{
		perror("fork error\n");
		exit(1);
	}
}

int main()
{
	char inputBuffer[MAXLINE];
	char *argv[MAXLINE/2-1];

	while(1)
	{
		printf("COMMAND->");
		cin.getline(inputBuffer,MAXLINE);
		if (strcmp(inputBuffer,"exit")==0)
		{
			printf("%s\n",inputBuffer);
			exit(0);
		}
		else
			setup(inputBuffer,argv);
	}
}
