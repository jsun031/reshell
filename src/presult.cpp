#include "ls.h"

int Print_result(char *listname[MAXNUM],int k,int flag_dir0,int Round ,int a, int R, int l,int flag_dir_doc)
{
	//printf("PR_al listname: ");
	allpt(k,listname);


	const int n1=sp_dir(k,listname);
	char *doc_name[MAXNUM];//n1 documents
	for(int i=0;i<n1;i++)
	{
		doc_name[i]=listname[i];
	}
	//printf("document name: ");
	allpt(n1, doc_name);

	char *dir_name[MAXNUM];//[k-n1]all the parameter
	for(int i=n1;i<k;i++)
	{
		dir_name[i-n1]=listname[i];
	}
	//printf("directory name: ");
	allpt(k-n1,dir_name);

	//int flag_dir_doc=0;

	if(n1>1)mysort(doc_name,n1);
	//printf("PR_al doc_name ");
	allpt(n1,doc_name);

	char *tmpdoc[MAXNUM];

	int if_doc=0;//if doc is display
	
	for (int i2=0;i2<n1;i2++)	
	{
		if(a==0)
		{	if(doc_name[i2][0]!='.')
			{
				if(l==1)
				{
					tmpdoc[i2]=doc_name[i2];
				}
				else if(l==0)
				{
					printf("%s\t", doc_name[i2]);
				}
				else
				{
					printf("error\n!");
					exit(1);
				}
				if_doc++;
			}
			else
			{
				continue;
			}
		}
		else if(a==1)
		{
			if(l==1)
			{
				tmpdoc[i2]=doc_name[i2];
			}
			else if(l==0)
			{
				printf("%s\t", doc_name[i2]);
			}
			else
			{
				printf("error\n!");
				exit(1);
			}
			if_doc++;
		}
	}

	if( l==1 )
	{
		lform(if_doc, tmpdoc, tmpdoc);
	}
	else if( l==0 )
	{
		if(if_doc)//end of doc, without -l
		{
			printf("\n");//all doc display finishes
		}
	}



	if(k-n1>1)mysort(dir_name,k-n1);
	allpt(k-n1,dir_name);
	for (int i2=0;i2<k-n1;i2++)
	{
		DIR *dirptr = NULL;
		struct dirent *entry;
		struct stat s;	
		char *sort_dir[MAXNUM];

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
			int errno=0;
			while ((entry = readdir(dirptr))!=NULL)//error check??
			{								
				if(a==0)
				{
					if(entry->d_name[0]!='.')
					{
						sort_dir[i3]=entry->d_name;
						i3++;
					}							
				}
				else if(a==1)
				{
					sort_dir[i3]=entry->d_name;
					i3++;
				}
			}
			if(errno!=0)
			{
				perror("readdir erroe!");
				exit(1);
			}
			if(i3>1)mysort(sort_dir,i3);
			if((Round==1)||((k-n1>1)&&(i3)))//newline between dir and dir
			{
				printf("\n");
			}

			if((i3)&&(flag_dir_doc==0)&&(if_doc))//newline between dor and dir
			{
				printf("\n");//all doc display finishes
				flag_dir_doc=1;
			}
			if(R==1 || ( (if_doc+k-n1)>=2 && i3!=0 ) )printf("%s:\n",dir_name[i2]);
			

			char tmp[MAXNUM][MAXLINE];
			char *tmpp[MAXNUM];
			
			for(int i4=0;i4<i3;i4++)
			{
				if(flag_dir0==1)
				{
					strcpy(dir_name[i2],".");
					flag_dir0=0;
				}		
				strcpy(tmp[i4],dir_name[i2]);
				if(dir_name[i2][strlen(dir_name[i2])-1]!='/')
				{
					strcat(tmp[i4],"/");
				}
				strcat(tmp[i4],sort_dir[i4]);
				tmpp[i4]=tmp[i4];
				if(l==0)
				{
					printf("%s\t",sort_dir[i4]);
				}
			}
			if( l==0 )
			{
				if(i3)//end of doc, without -l
				{
					printf("\n");//all doc display finishes
				}
			}

			if(l==1)lform(i3, tmpp,sort_dir);

			if(i3)
			{
				char *tmp_arr[MAXNUM];
				int i5=0;
				for (int i=0;i<i3;i++)//. .. should not be used
				{
					if( (strcmp(sort_dir[i],".")!=0)&&(strcmp(sort_dir[i],"..")!=0) )
					{
						tmp_arr[i5]=tmp[i];
						i5++;
					}
				}

				const int n11=sp_dir(i5,tmp_arr);//n11 doc in spdir
			
				char *tmp_dir[MAXNUM];//[i3-n11]all the dir
				for(int i=n11;i<i5;i++)
				{
					tmp_dir[i-n11]=tmp_arr[i];
				}

				//printf("directory name: ");
				allpt(i5-n11,tmp_dir);

				Round=1;
				if(R==1 && (i5-n11) )Print_result( tmp_dir,i5-n11, flag_dir0,Round,a,R,l,flag_dir_doc);
			}

			if(closedir(dirptr)!=0)
			{
				perror("closedir error!\n"); 
				exit(1);
			}//error check
			
			
		}

	}
	return 0;	
}
