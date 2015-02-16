#include "ls.h"	
	
int main(int argc,char** argv)
{
	int k=setaprt(argc,argv);//parameter=argv[k]~[argc-1], name list=argv[1]-argv[k-1]
	
	char *parameter[MAXNUM];//[argc-k]all the parameter
	for(int i=k;i<argc;i++)
	{
		parameter[i-k]=argv[i];
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
	//printf("whether it is -a: %d\n",a);
	int flag_dir0=0;

	char listnamesb[MAXNUM][MAXLINE];
	char *listname[MAXNUM];//[k]all the listname
	if(k<=1)//no list name, it should be the current
	{
		char buf[MAXLINE];
		//strcpy(listname[0],".");
		listname[0]=getcwd(buf,MAXLINE);
		flag_dir0=1;
	}
	else
	{
		for(int i=0;i<k-1;i++)
		{
			listname[i]=argv[i+1];
		}
		k=k-1;
	}//k is the number of list names;
	//printf("listname: ");
	for (int i=0;i<k;i++)
	{
		strcpy(listnamesb[i],listname[i]);
		listname[i]=listnamesb[i];
	}
	allpt(k,listname);
	Print_result( listname,k, flag_dir0,0,a,R,l,0);
	
	return 0;
}
