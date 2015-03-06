#include "rshell.h"

int pipesetup(char inputBuffer[])//deal with pipe
{
	char *p;//not malloc(MAXLINE*sizeof(char));
	char *input[MAXLINE];
	int num=0;
	for (p=inputBuffer; ;p++)
	{
		if(*p=='\0')
		{
			break;
		}
		// not malloc(MAXLINE*sizeof(char));
		input[num]=p;
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
		num++;
	}//i argv[]from 0 to i-1
	/*for (int j=0;j<num;j++)
	{
		printf("input[%d]=%s\n",j,input[j]);// , mark[%d]=%d ,j,mark[j]
	}*/
    	int status=exe(input,num);
	return status;
}
