#include<unistd.h>
#include <stdio.h>
#include <wait.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int num=2;
	printf("This is parent process%d\n",getpid());
	char string[2][10];
	strcpy(string[0],"ls");
	strcpy(string[1],"head");
	char *argv[2][10];
	argv[0][0]=string[0];
	argv[0][1]=NULL;
	argv[1][0]=string[1];
	argv[1][1]=NULL;
	pid_t p1,p2;
	int pipe_id[7][2];
	if(pipe(pipe_id[0]) < 0)
	{
		perror("pipe");
	}
	for(int i=0;i<num;i++)
	{
		if((p1=fork())==0)
		{
			printf("This is child_1 process%d\n",getpid());
			if(i!=num-1)
			{
				if(-1==close(pipe_id[i][0]))
                {
                    perror("close 0 error in child!");
                    exit(1);
                }
				if(dup2(pipe_id[i][1], 1) == -1)
				{
					perror("1st dup2");
					exit(1);
				}

				if(-1==close(pipe_id[i][1]))
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
		if(i!=num-1)
		{
			if(-1==close(pipe_id[i][1]);)
            {
                perror("close 1 error in parent!");
                exit(1);
            }
			if(dup2(pipe_id[i][0], 0) == -1)
			{
				perror("2nd p dup2");
				exit(1);
			}
			if(-1==close(pipe_id[i][0]))
            {
                perror("close 0 error in parent!");
                exit(1);
            }
		}

perror("1\n");

		int status;
		if(-1==waitpid(p1,&status,0))
		{
			perror("error");
			exit(1);
		}
		printf("This is parent process%d\n",getpid());

	}


	return 0;

}
