#include "ls.h"

bool cmp_dot(char a[], char b[])
{
	if (strlen(a)<strlen(b))
	{
		return false;
	}
	else
	{
		return true;
	}	
}

bool if_all_dot(char a[])
{
	int j=strlen(a);
	for(int l=0;l<j;l++)
	{
		if(a[l]!='.')return false;
	}
	return true;
}

	
char* convert(char a[])//remain only a~z and 0~9
{
	char*q;
	int j=strlen(a);
	int flag=0;
	for(int l=0;l<j;l++)
	{
		if(a[l]!='.')flag=1;
	}
	
	if(flag==1)
	{
		int i=0;
		int k=0;
		while(k<j)
		{
		
			while((a[k]<'0'||(a[k]>'9'&&a[k]<'A')||(a[k]>'Z'&&a[k]<'a')||a[k]>'z')&&k<j)
			{
				k++;
			}
			while((a[k]>='A'&&a[k]<='Z')&&k<j)
			{
				a[i]=a[k]+'a'-'A';
				k++;
				i++;
			}
			while(((a[k]>='a'&&a[k]<='z')||(a[k]>='0'&&a[k]<='9'))&&k<j)
			{
				a[i]=a[k];
				k++;
				i++;
			}
		}
		a[i]='\0';
	}
	q=&a[0];
	return q;
}

bool compare(char *p1,char *p2)//sort alphabetically
{
	//if(strcmp(p1,'\0')==0){return true;}
	//if(strcmp(p2,'\0')==0){return false;}
	
	char q1[MAXLINE];
	char q2[MAXLINE];
	strcpy(q1,p1);
	strcpy(q2,p2);
	if( (if_all_dot(p1) )&&( if_all_dot(p2) ) )
	{
		return cmp_dot(p1,p2);
	}
	char *q3;
	if (if_all_dot(q1)) return false;	
	q3=convert(q1);

	
	char *q4;
	if(if_all_dot(q2)) return true;
	q4=convert(q2);

	if (strcmp(q3,q4)<0) return false;
	else return true;
}


void mysort(char *list[], int num)
{
	char *tmp;
	for( int j=0;j<num;j++)
	{
		for(int i=0;i<num-j-1;i++)
		{
			if(compare(list[i],list[i+1]))
			{
				tmp=list[i];
				list[i]=list[i+1];
				list[i+1]=tmp;	
			}
		}
	}
}

int setaprt(int argc,char**argv)//need to work to separate name list and parameters: put them in the order:name in the front, p in the rear; use last position to store name numbers.
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
{/*
	printf("%d in total\n",argc);//show the input
	for(int i=0;i<argc;i++)
	{
		printf("[%d]= %s\n",i,argv[i]);

	}*/
}
int sp_dir(int argc,char**argv)//need to work to separate dir list and documents: put them in the order:documents in the front, dirs in the rear; use return valve to document number. dit at least 1
{
	int i=0,j=0;
	char *p;
	while(i<argc-j)
	{
		struct stat s;
		if(stat(argv[i],&s)!=0)//error check
		{
			perror("stat error in sp_dir");
			exit(1);
		}
		if(s.st_mode&S_IFDIR)//dir
		{
			struct stat s1;
			if (stat(argv[argc-1-j],&s1)!=0)
			{
				perror("stat error in sp_dir2");
			}
			while((s1.st_mode&S_IFDIR)&&(argc-1-j)>i)//find the last one not dir
			{
				j++;
				if (stat(argv[argc-1-j],&s1)!=0)
				{
					perror("stat error in sp_dir2");
				}
			}
			if((argc-1-j)<=i)//all are dir
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
	return i;//i documents
}
