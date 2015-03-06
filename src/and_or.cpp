#include "rshell.h"

int and_or(char* inputBuffer)
{
	char *p;//not malloc(MAXLINE*sizeof(char));
	char *input[MAXLINE];
	int i=0;
	char flag[MAXLINE/2];
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
			if(*q!='&'&&*q!='\0'&&*q!='|')
			{
				continue;
			}
			else if(*q=='&')
			{
				flag[i]=0;
				if(*(++q)=='&')
				{
					*q=' ';
					*(--q)='\0';
					p=q;
					break;
				}
				else
				{
					--q;
					p=q;
					*q='\0';
					break;
				}
			}
			else if(*q=='|')
			{
				flag[i]=1;
				if(*(++q)=='|')
				{
					*q=' ';
					*(--q)='\0';
					p=q;
					break;
				}
				/*else// single | is pipe
				{
					--q;
					p=q;
					*q='\0';
					break;
				}*/
			}
			else if(*q=='\0')
			{
				p=q;
				p--;//as p++ forloop
				break;
			}
		}
		i++;
	}//i argv[]from 0 to i-1
	//printf("%d segements and_or\n",i) ;
	int result;
	int mark=0;//true, need to continue
	/*for (int j=0;j<i;j++)
	        printf("input[%d]=%s\n",j,input[j]);*/
	for (int j=0;(j<i)&&(mark==0);j++)
	{
		result=pipesetup(input[j]);
        //printf("input[%d] return value is %d\n",j,result);
   		if (flag[j]==0)
		{
			mark=result+mark;
		}
		else if(flag[j]==1)
		{
			mark=(result==0);
		}
		//printf("execvp status%d\n",result);
	}
	return 0;
}
