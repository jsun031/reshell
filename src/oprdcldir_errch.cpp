#include <stdio.h>
#include <dirent.h>
#include <string.h>
//need to work to separate name list and parameters
//1 put them in the order:name in the front, p in the rear.use last position to store name numbers.
int setaprt(int argc,char**argv)
{
	int i=0,j=0;
	char *p;
	while(i<argc-j)
	{
		if(argv[i][0]=='-')//initiate with'-'
		{
			while(argv[argc-1-j][0]=='-'&&(argc-1-j)>i)//find the last one not initiate with'-'
			{
				j++;
			}
			if((argc-1-j)<=i)//all initiate without '-'
			{
				break;
			}
			p=argv[i];//swap
			argv[i]=argv[argc-1-j];
			argv[argc-1-j]=p;
			j++;
		}
		i++;
	}
	return i;//i listnames
}

void allpt(int argc,char **argv)
{
	printf("%d in total\n",argc);//show the input
	for(int i=0;i<argc;i++)
	{
		printf("[%d]= %s\n",i,argv[i]);

	}
}

int main(int argc,char** argv)
{
	DIR *dirptr = NULL;
	struct dirent *entry;
	allpt(argc,argv);
	
	/*for(int j=0;j<argc-1;j++)//ignore(delete) argv[0], move other backward
	{
		argv[j]=argv[j+1];
	}
	argc=argc-1;*/

	int k=setaprt(argc,argv);//parameter=argv[k]~[argc-1], name list=argv[1]-argv[k-1]
	allpt(argc,argv);
	printf("%d list names\n",k);

	char *parameter[argc-k];
	for(int i=k;i<argc;i++)
	{
		parameter[i-k]=argv[i];
	}
	allpt(argc-k,parameter);	

	char *listname[k];
	if(k<=1)//no list name, it should be the current
	{
		//const char v[]=".";
		strcpy(argv[0],".");
		listname[0]=argv[0];
	}
	else
	{
		for(int i=0;i<k;i++)
		{
			listname[i]=argv[i+1];
		}
	}
		
	int a=0,l=0,R=0;//mark if there exists a "-a", "-l" or "-R"
	for (int i1=0;i1<argc-k;i1++ )
	{
		int j=1;
		while(parameter[i1][j]!='\0')
		{
			if(parameter[i1][j]=='a')
			{
				a=1;
			}
			if(parameter[i1][j]=='l')
			{
				l=1;
			}
			if(parameter[i1][j]=='R')
			{
				R=1;
			}
			j++;
		}
	}
	printf("%d\n",a);

/*	if(argc>1)//more than 1 dir
	{
		printf("the program can only deal with one dir at once\n");
		return 1;
	}*/

	if((dirptr = opendir(listname[0])) == NULL)//errot check
	{
		perror("open dir error !\n");
		return 1;
	}
	else//normal display
	{
 
		while (entry = readdir(dirptr))//error check??
		{ 
			if(a==1)
			{
				printf("%s  ", entry->d_name);
			}
			else
			{
			 	if(entry->d_name[0]!='.')
				{
					printf("%s  ", entry->d_name);
				}
				else
				{
					continue;
				}
			}
		}
		printf("\n");
		//printf("%s\n",entry);
		if(closedir(dirptr)!=0){perror("closedir error!\n"); }//error check
	}
	return 0;
}
