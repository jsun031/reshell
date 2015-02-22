#include "rshell.h"

int exe(char *input[MAXLINE],int num)
{
	printf("pipe num is %d\n",num);
	char *argv[MAXLINE/2-1][MAXLINE/2-1];
	int mark[MAXLINE/2-1][MAXLINE/2-1];// relation between i-1 and i
	for( int j=0;j<num;j++)
	{
		for(int i=0;i<MAXLINE/2-1;i++)
        {
            mark[j][i]=0;
        }
	}
	int length[MAXLINE/2-1];
	for (int j=0;j<num;j++)
	{
		length[j]=0;
		argv[j][length[j]]=NULL;
		char *p;//=(char*)malloc(MAXLINE*sizeof(char));
		//int gt_mark=0;//number of continuous greater mark
		for (p=input[j]; ;p++)
		{
			//int continue_num;//continue mark number
			while(*p==' '||*p=='\t')
			{
				p++;
			}
			while(*p=='>')
			{
				p++;
				mark[j][length[j]]++;
			}
			while(*p==' '||*p=='\t')
			{
				p++;
			}
			if(*p=='\0')
				break;
			if(*p=='>')
			{
				printf("> grammar error!\n");
				exit(1);
			}
			argv[j][length[j]++]=p;
			while (*p!=' '&&*p!='\0'&&*p!='\t'&&*p!='>')
				p++;
			if(*p=='\0')
			{
				break;
			}
			if (*p=='>')
			{
				mark[j][length[j]]++;//>
			}
			*p='\0';
			p++;
			while(*p==' '||*p=='\t')
			{
				p++;
			}
			p--;
		}
		argv[j][length[j]]=NULL;
	}//length[i] stands for the arguement number of argv[i]

	for (int i=0;i<num;i++)
	{
		for(int i1=0;i1<length[i];i1++)
		{
			printf("argv[%d][%d]=%s mark[%d][%d]=%d\n",i,i1,argv[i][i1],i,i1,mark[i][i1]);
            if(mark[i][i1]>2)
            {
                printf("wrong > number!\n");
                exit(1);
            }
		}
	}
	pid_t p1;
	pid_t pp[MAXLINE];//for wait at last
	int pipe_id[2];

	int savestdin;
	if(-1 == (savestdin = dup(0)))
		perror("wrong with calling dup");
	//int flag=0;//> happen, then, there is no origin pipe.
	int gt_exist[MAXLINE/2-1];
	for( int i=0;i<num;i++)
	{
		for( int j=0;j<length[i];j++)
		{
			//gt_exist[i]=mark[i][j];
			if(mark[i][j]>0)//> exist
			{
				gt_exist[i]=1;
			}
		}
	}
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

 			char *arr[MAXLINE/2-1];

			int tmp=0;
			for( int j=0;j<length[i];j++)
 			{
 				if(mark[i][j]==0)
 				{
 					arr[tmp++]=argv[i][j];
 				}
 			}
 			if(gt_exist[i]==0)
 			{
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

					/*if(-1==close(pipe_id[1]))
					{
					    perror("close 1 error in child!");
					    exit(1);
					}*/
				}
			}
			else if (gt_exist[i]==1)
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
			}
			if(execvp(arr[0],arr)!=0)//else is no used, even if succeed,
			{
				perror("execvp fail");
				exit(1);
			}
			return 0;//这个地方非常关键
		}
		else if(p1<0)
		{
			perror("fork error!");
			exit(1);
		}
		else if(p1>0)
		{
			if(gt_exist[i]==0)
			{
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
					/*if(-1==close(pipe_id[0]))
					{
						perror("close 0 error in parent!");
						exit(1);
					}*/
				}
			}
			else if (gt_exist[i]==1)
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

				for(int j=0;j<length[i];j++)
				{
					if(mark[i][j]==1||mark[i][j]==2)
					{
                        int file2;
                        if(mark[i][j]==1)
                        {
                            file2=open(argv[i][j],O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
						}
                        else if(mark[i][j]==2)
                        {
                            file2=open(argv[i][j],O_WRONLY|O_CREAT|O_APPEND,S_IRWXU);
						}

                        if(file2<0)
						{
							perror("open file2 error");
							exit(1);
						}
						char str[BUFSIZ];
						ssize_t readsize=read(0,str,BUFSIZ);
						if(readsize<0)
						{
							perror("read error!");
							exit(1);
						}
						while(readsize>0)
						{
							if(-1==write(file2,str,readsize))
							{
								perror("write error!");
								exit(1);
							}
							readsize=read(0,str,BUFSIZ);
						}
						if(readsize<0)
						{
							perror("read error!");
							exit(1);
						}
						if(close(file2)<0)
						{
							perror("close 2 error");
							exit(1);
						}
					}
				}
			}
		}
		perror("1\n");
	}

	if(-1 == dup2(savestdin,0))//restore stdin
		perror("There is an error with dup2. ");


	int status[MAXLINE];
    int sum=0;
	for (int i=0;i<num;i++)
	{
		if(-1==waitpid(pp[i],&status[i],0))
		{
			perror("error");
			exit(1);
		}
        printf("child[%d] status is %d\n",i,status[i]);
        sum=sum+status[i];
	}
		printf("This is parent process%d\n",getpid());
        printf("sum of status is %d\n",sum);
	return sum;
}
