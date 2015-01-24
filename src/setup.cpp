#include "rshell.h"

int setup(char inputBuffer[])
{
	int i;
	char *argv[MAXLINE/2-1];
	char *p;//=(char*)malloc(MAXLINE*sizeof(char));
	i=0;
	for (p=inputBuffer; ;p++)
	{
		while(*p==' '||*p=='\t')
		{
			p++;
		}
		if(*p=='\0')
			break;
		//argv[i]=(char*)malloc((MAXLINE/2-1)*sizeof(char));
		argv[i++]=p;
		while (*p!=' '&&*p!='\0'&&*p!='\t')
			p++;
		if(*p=='\0')
			break;
		*p='\0';
		p++;
		while(*p==' '||*p=='\t')
		{
			p++;
		}
		p--;
	}
	//free (p);
	argv[i]=NULL;
	pid_t pid;
	pid=fork();
	if (pid==0)
	{
		if(execvp(argv[0],argv)!=0)//else is no used, even if succeed, 
		{
			perror("execvp fail");
			exit(1);
		}
	}
	else
		if(pid>0)
		{
			int status;
			if(-1==waitpid(pid,&status,0))
			{
				perror("wait failure");
				exit(1);
			}
			else
			{
				return status;
			}
		}
		else if(pid<0)
		{
			perror("fork error\n");
			exit(1);
		}
		return 0;
}
