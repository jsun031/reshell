#include "rshell.h"

int smcln(char inputBuffer[])
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
			if(*q!=';'&&*q!='\0'&&*q!='#')
			{
				continue;
			}
			else if(*q==';')
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
			else if(*q=='#')
			{
				*q='\0';
				p=q;
				p--;
				break;//as p++ forloop, guarantee exit
			}
		}
		i++;
	}//i argv[]from 0 to i-1
    //printf("%d segements by semicolon\n",i);
	for (int j=0;j<i;j++)
	{
		and_or(input[j]);
	}
	return 0;
}

