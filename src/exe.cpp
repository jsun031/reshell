#include "rshell.h"

int exe(char *input[MAXLINE],int num)
{
	char *argv[MAXLINE/2-1][MAXLINE/2-1];
	for (int j=0;j<num;j++)
	{
		int i;
		char *p;//=(char*)malloc(MAXLINE*sizeof(char));
		i=0;
		for (p=input[j]; ;p++)
		{
			while(*p==' '||*p=='\t')
			{
				p++;
			}
			if(*p=='\0')
				break;
			argv[j][i++]=p;
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
		argv[j][i]=NULL;
	}
	for (int i=0;i<num;i++)
	{
		int i1=0;
		while(argv[i][i1]!=NULL)
		{
			printf("argv[%d][%d]=%s\n",i,i1,argv[i][i1]);
			i1++;
		}
	}	
	pid_t p1;
	pid_t pp[MAXLINE];//for wait at last
	int pipe_id[2];
	
	int savestdin;
	if(-1 == (savestdin = dup(0)))
		perror("wrong with calling dup");
	
	for(int i=0;i<num;i++)
	{
		if(pipe(pipe_id) < 0)
		{
			perror("pipe");
		}
		if((p1=fork())==0)
		{
			pp[i]=p1;
			printf("This is child_1 process%d\n",getpid());

			if (i!=num-1)// | mark[i]==5&&
			{
				if(-1==close(pipe_id[0]))
				{
				    perror("close 0 error in child!");
				    exit(1);
				}
				if(dup2(pipe_id[1], 1) == -1)
				{
					perror("1st dup2");
					exit(1);
				}

				if(-1==close(pipe_id[1]))
				{
				    perror("close 1 error in child!");
				    exit(1);
				}
			}
 
			if(execvp(argv[i][0],argv[i])!=0)//else is no used, even if succeed,
			{
				perror("execvp fail");
				exit(1);
			}
			return 0;//这个地方非常关键
		}
		if ( i!=num-1)// | mark[i]==5&&
		{
			if(-1==close(pipe_id[1]))
			{
				perror("close 1 error in parent!");
				exit(1);
			}
				if(dup2(pipe_id[0], 0) == -1)
				{
					perror("2nd p dup2");
					exit(1);
				}
				if(-1==close(pipe_id[0]))
			{
				perror("close 0 error in parent!");
				exit(1);
			}
		}
		perror("1\n");
		
	}
	
	if(-1 == dup2(savestdin,0))//restore stdin
		perror("There is an error with dup2. ");

	
	int status;
	for (int i=0;i<num;i++)
	{
		if(-1==waitpid(pp[i],&status,0))
		{
			perror("error");
			exit(1);
		}
		//printf("This is parent process%d\n",getpid());
	}
	return 0;
}
