#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <iostream>
#include <stdlib.h>
#define MAXLINE 80
using namespace std;

void setup(char inputBuffer[],char *argv[])
{
	int i,j;
	char *p;
	i=0;
	for (p=inputBuffer; ;p++)
	{
		argv[i++]=p;
		while (*p!=' '&&*p!='\0')
			p++;
		if(*p=='\0')
			break;
		*p='\0';
	}
	argv[i]=NULL;
	pid_t pid;
	pid=fork();
	if (pid==0)
	{
		if(execvp(argv[0],argv)!=0)
		{
			perror("execvp fail");
			exit(1);
		}
		else
		{
			printf("Command accept\n");
		}
	}
	else
		if(pid>0)
		{
			if(-1==wait(0))
			{
				perror("wait failure");
				exit(1);
			}
		}
		else if(pid<0)
		{
			perror("fork error\n");
		}
}


int main()
{
	char inputBuffer[MAXLINE];
	char *argv[MAXLINE/2-1];

	while (1)
	{
		printf ("COMMAND->");
		cin.getline(inputBuffer,MAXLINE);
		printf("Show\n");
		if ((strcmp(inputBuffer, "exit") == 0))
			exit(1);
	}
	return 0;
}
