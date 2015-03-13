#include "rshell.h"

int childp1;

int setpath(char *dir_name[],char *argv,char *key_name)//deal with pipe
{
    char *once;
    char Buffer[MAXLINE];
	char *getenvBuffer;
	once=getenv("PATH"); /* get the comspec environment parameter */
    strcpy(Buffer,once);
    getenvBuffer=Buffer;
	char *p;//not malloc(MAXLINE*sizeof(char));
	char *input[MAXLINE];
	int num=0;
	for (p=getenvBuffer; ;p++)
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
		strcpy(dir_name[j],input[j]);
		strcat(dir_name[j],"/");
		//printf("input[%d]=%s\n",j,input[j]);// , mark[%d]=%d ,j,mark[j]
	}
	int i4=0;
	for (int i2=0;i2<num;i2++)
	{
		DIR *dirptr = NULL;
		struct dirent *entry;
		struct stat s;
		//char *sort_dir[MAXNUM];
		if(stat(dir_name[i2],&s)!=0)
		{
			perror("stat dir goes wrong!\n");
			exit(1);
		}
		if((dirptr = opendir(dir_name[i2])) == NULL)//errot check
		{
			perror("open dir error !\n");
			exit (1);
		}
		else//normal display
		{
			int i3=0;
			errno=0;
			while ((entry = readdir(dirptr))!=NULL)//error check??
			{
				if(strcmp(entry->d_name,argv)==0)
				{
					strcpy(key_name,dir_name[i2]);
					strcat(key_name,argv);
                    i3++;
				}
			}
			if(errno!=0)
			{
				printf("errno=%d\n",errno);
				char * mesg = strerror(errno);
				printf("Mesg:%s\n",mesg);
				perror("readdir erroe!");
				exit(1);
			}
            if(i3>0)
            {
                i4=1;
            }
		}
	}
	return i4;
}

void handle_signal(int sig)
{
	// cout << "in signal " << childPid << endl;
	cout << endl;
	if(childp1 != 1)
	{
		if(-1 == kill(childp1,SIGKILL))
			perror("kill");
	}
}

int exe(char *input[MAXLINE],int num,int *exitptr)
{
	//printf("pipe num is %d\n",num);
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
			while(*p==' '||*p=='\t'||*p=='<')
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
			while (*p!=' '&&*p!='\0'&&*p!='\t'&&*p!='>'&&*p!='<')
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
			while(*p==' '||*p=='\t'||*p=='<')
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
			//printf("argv[%d][%d]=%s mark[%d][%d]=%d\n",i,i1,argv[i][i1],i,i1,mark[i][i1]);
			if(mark[i][i1]>2)
			{
				printf("wrong > number!\n");
				exit(1);
			}
			if(strcmp(argv[i][i1],"exit")==0)
			{
				if(num==1)
				{	
					*exitptr=1;
				}
				return 0;
			}
		}
	}

	pid_t pp[MAXLINE];//for wait at last
	int pipe_id[2];

	int savestdin;
	if(-1 == (savestdin = dup(0)))
		perror("wrong with calling dup");
	//int flag=0;//> happen, then, there is no origin pipe.
	int gt_exist[MAXLINE/2-1];
	for( int i=0;i<num;i++)
	{
		gt_exist[i]=0;
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
		errno=0;
		signal(SIGINT, handle_signal);
		if(errno!=0)
		{
			perror("signal error!");
			exit(1);
		}			
		if((childp1=fork())==0)
		{
			pp[i]=childp1;

 			char *arr[MAXLINE/2-1];

			int tmp=0;
			for( int j=0;j<length[i];j++)
 			{
 				if(mark[i][j]==0)
 				{
 					arr[tmp++]=argv[i][j];
 				}
 			}
        		arr[tmp]='\0';//exe requires last argument to be null
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

					if(-1==close(pipe_id[1]))
					{
					    perror("close 1 error in child!");
					    exit(1);
					}
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

				if(-1==close(pipe_id[1]))
				{
					perror("close 1 error in parent!");
					exit(1);
				}
				if(i==num-1)
				{
					gt_exist[i]=0;
				}
			}
	            	if(strcmp(arr[0],"cd")==0)
	            	{
	                	//printf("current working directory: %s\n", getcwd(s,100));
	                	if(chdir(arr[1])!=0)
	                	{
	                	    perror("chdir\n");
	                	    exit(1);
	                	}
	                	return 0;
	            	}
			char separatestring[MAXNUM][MAXLINE];
			char *dir_name[MAXNUM];
			for(int i1=0;i1<MAXNUM;i1++)
			{
				dir_name[i1]=separatestring[i1];
			}
			char keyname[MAXLINE]="\0";
			char *key=keyname;
			if(strcmp(arr[0],"\0")==0)
			{
				printf("you need to give 1 argement\n");
				return 0;
			}
		   	int num=setpath(dir_name,arr[0],key);
			if(num!=0)
			{
				if(execv(key,arr)!=0)
				{
					perror("execv fail");
					exit(1);
				}
			}
			else
			{	
				if(execv(arr[0],arr)!=0)
				{
					perror("execv fail");
					exit(1);
				}
			
				printf("No valid path!\n");
			}
			return 0;//这个地方非常关键
		}
		else if(childp1<0)
		{
			perror("fork error!");
			exit(1);
		}
		else if(childp1>0)
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
					if(-1==close(pipe_id[0]))
					{
						perror("close 0 error in parent!");
						exit(1);
					}
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
						    	if(file2<0)
							{
								perror("open file2 error");
								exit(1);
							}
						}
						else if(mark[i][j]==2)
						{
							file2=open(argv[i][j],O_WRONLY|O_CREAT|O_APPEND,S_IRWXU);
							if(file2<0)
							{
								perror("open file2 error");
								exit(1);
							}
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
        sum=sum+status[i];
	}
	return sum;
}
