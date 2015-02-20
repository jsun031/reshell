#include "rshell.h"

int pipebuf(char inputBuffer[])
{
	char *p;//not malloc(MAXLINE*sizeof(char));
	char *input[MAXLINE];
	int i=0;
	for (p=inputBuffer; ;p++)
	{
		if(*p=='\0')
		{
			break;
		}
		// not malloc(MAXLINE*sizeof(char));
		input[i]=p;
		char*q;//not malloc(MAXLINE*sizeof(char));
		for(q=p;;q++)
		{
			if(*q!='|'&&*q!='\0')
			{
				continue;
			}
			else if(*q=='|')
			{
				*q='\0';
				p=q;
				break;
			}
			else if(*q=='\0')
			{
				p=q;
				p--;//as p++ forloop, guarantee exit
				break;
			}
		}
		i++;
	}//i argv[]from 0 to i-1
	for (int j=0;j<i;j++)
	{
		setup(input[j]);
	}
	return 0;
}
int setup(char inputBuffer[])
{
	int i0;
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
	argv[i0]=NULL;
	return 0;
}
