#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#define MAXLINE 80
using namespace std;

int setpath(char inputBuffer[],char *returnvalue[])//deal with pipe
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
			if(*q!=':'&&*q!='\0')
			{
				continue;
			}
			else if(*q==':')
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
	for (int j=0;j<num;j++)
	{
		strcpy(returnvalue[j],input[j]);
		strcat(returnvalue[j],"/");
		printf("input[%d]=%s\n",j,input[j]);// , mark[%d]=%d ,j,mark[j]
	}
	return num;
}

int main(void)
{
	char *s;
	s=getenv("PATH"); /* get the comspec environment parameter */
	char separatestring[10][MAXLINE];
	char *septr[10];
	for(int i=0;i<10;i++)
	{
		septr[i]=separatestring[i];
	}
	int num=setpath(s,septr);
	for(int i=0;i<num&&septr[i]!=NULL;i++)
	{
		printf("separastring[%d]=%s\n",i,septr[i]);
	}
	return 0;
}
