#include "ls.h"
int PR_al(char *listname[MAXNUM],int k,int flag_dir0,int Rround)
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

	int flag_dir_doc=0;

	if(n1>1)mysort(doc_name,n1);
	//printf("PR_al doc_name ");
	allpt(n1,doc_name);

	char*tmpdoc[MAXNUM];
	int if_doc=0;//if doc is display
	for (int i2=0;i2<n1;i2++)	
	{
		//if(doc_name[i2][0]!='.')
		//{
			//lprint(doc_name[i2]);
			//printf("%s\n", doc_name[i2]);
		tmpdoc[i2]=doc_name[i2];
			if_doc++;
		/*}
		else
		{
			continue;
		}*/
	}
	lform(if_doc, tmpdoc, tmpdoc);

	/*if(if_doc)//end of doc, without -l
	{
		printf("\n");//all doc display finishes
	}*/



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
			while ((entry = readdir(dirptr))!=NULL)//error check??
			{								
				//if(entry->d_name[0]!='.')
				//{
					sort_dir[i3]=entry->d_name;
					i3++;
				//}							
				//printf("%s\t", entry->d_name);
			}
			if(i3>1)mysort(sort_dir,i3);
			if((Rround==1)||((k-n1>1)&&(i3)))//newline between dir and dir
			{
				printf("\n");
			}
			if((i3)&&(flag_dir_doc==0)&&(if_doc))//newline between dor and dir
			{
				printf("\n");//all doc display finishes
				flag_dir_doc=1;
			}

			if(k>=2||Rround==1)
			{
				printf("%s:\n",dir_name[i2]);
			}

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
				//lprint(tmp[i4]);
				//printf("%s\n",sort_dir[i4]);
			}
			lform(i3, tmpp,sort_dir);
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
				Rround=1;
				if(i5-n11)PR_al( tmp_dir,i5-n11, flag_dir0,Rround);
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

int PR_l(char *listname[MAXNUM],int k,int flag_dir0,int Rround)//lR
{

	//printf("PR_l listname: ");
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

	int flag_dir_doc=0;

	if(n1>1)mysort(doc_name,n1);
	//printf("PR_l doc_name ");
	allpt(n1,doc_name);

	char*tmpdoc[MAXNUM];
	int if_doc=0;//if doc is display
	for (int i2=0;i2<n1;i2++)	
	{
		if((doc_name[i2][0]!='.')||((doc_name[i2][0]=='.') &&( doc_name[i2][1]=='/') ))
		{
			//lprint(doc_name[i2]);
			//printf("%s\n", doc_name[i2]);
			tmpdoc[i2]=doc_name[i2];
			if_doc++;
		}
		else
		{
			continue;
		}
	}
	lform(if_doc, tmpdoc, tmpdoc);


	/*if(if_doc)//end of doc, without -l
	{
		printf("\n");//all doc display finishes
	}*/



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
			while ((entry = readdir(dirptr))!=NULL)//error check??
			{								
				if(entry->d_name[0]!='.')
				{
					sort_dir[i3]=entry->d_name;
					i3++;
				}							
			}
			if(i3>1)mysort(sort_dir,i3);
			if((Rround==1)||((k-n1>1)&&(i3)))//newline between dir and dir, (k>1,if_doc=0->flag=0,need newline)(k=1,if_doc>0->
			{
				printf("\n");
			}
			if((i3)&&(flag_dir_doc==0)&&(if_doc))//newline between dor and dir
			{
				printf("\n");//all doc display finishes
				flag_dir_doc=1;
			}

			if(k>=2||Rround==1)
			{
				printf("%s:\n",dir_name[i2]);
			}
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
			}
			lform(i3, tmpp,sort_dir);
			
			if(i3)
			{
				char *tmp_arr[MAXNUM];
				int i5=0;
				for (int i=0;i<i3;i++)
				{
					if(sort_dir[i][0]!='.')
					{
						tmp_arr[i5]=tmp[i];
						i5++;
					}
				}
				
				const int n11=sp_dir(i5,tmp_arr);
				
				char *tmp_dir[MAXNUM];//[i3-n11]all the parameter
				for(int i=n11;i<i5;i++)
				{
					tmp_dir[i-n11]=tmp_arr[i];
				}
				//printf("directory name: ");
				allpt(i5-n11,tmp_dir);
				Rround=1;
				if(i5-n11)PR_l( tmp_dir,i5-n11, flag_dir0,Rround);
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

int PR_a(char *listname[MAXNUM],int k,int flag_dir0,int Rround)
{
	//printf("PR_a listname: ");
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

	int flag_dir_doc=0;

	if(n1>1)mysort(doc_name,n1);
	//printf("PR_al doc_name ");
	allpt(n1,doc_name);
	int if_doc=0;//if doc is display
	for (int i2=0;i2<n1;i2++)	
	{
		//if(doc_name[i2][0]!='.')
		//{
			//lprint(doc_name[i2]);
			printf("%s\t", doc_name[i2]);
			if_doc++;
		/*}
		else
		{
			continue;
		}*/
	}

	if(if_doc)//end of doc
	{
		printf("\n");//all doc display finishes
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
			while ((entry = readdir(dirptr))!=NULL)//error check??
			{								
				//if(entry->d_name[0]!='.')
				//{
					sort_dir[i3]=entry->d_name;
					i3++;
				//}							
				//printf("%s\t", entry->d_name);
			}
			if(i3>1)mysort(sort_dir,i3);
			if((Rround==1)||((k-n1>1)&&(i3)))//newline between dir and dir
			{
				printf("\n");
			}
			if((i3)&&(flag_dir_doc==0)&&(if_doc))//newline between dor and dir
			{
				printf("\n");//all doc display finishes
				flag_dir_doc=1;
			}

			if(k>=2||Rround==1)
			{
				printf("%s:\n",dir_name[i2]);
			}

			char tmp[MAXNUM][MAXLINE];
			
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
				//lprint(tmp[i4]);
				printf("%s\t",sort_dir[i4]);
			}
			if(i3)
			{
				printf("\n");
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
				Rround=1;
				if(i5-n11)PR_a( tmp_dir,i5-n11, flag_dir0,Rround);
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


int PR(char *listname[MAXNUM],int k,int flag_dir0,int Rround)//R
{

	//printf("PR listname: ");
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

	int flag_dir_doc=0;

	if(n1>1)mysort(doc_name,n1);
	//printf("PR_al doc_name ");
	allpt(n1,doc_name);
	int if_doc=0;//if doc is display
	for (int i2=0;i2<n1;i2++)	
	{
		if((doc_name[i2][0]!='.')||((doc_name[i2][0]=='.') &&( doc_name[i2][1]=='/') ))
		{
			//lprint(doc_name[i2]);
			printf("%s\t", doc_name[i2]);
			if_doc++;
		}
		else
		{
			continue;
		}
	}

	if(if_doc)//end of doc, without -l
	{
		printf("\n");//all doc display finishes
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
			while ((entry = readdir(dirptr))!=NULL)//error check??
			{								
				if(entry->d_name[0]!='.')
				{
					sort_dir[i3]=entry->d_name;
					i3++;
				}							
			}
			if(i3>1)mysort(sort_dir,i3);
			if((Rround==1)||((k-n1>1)&&(i3)))//newline between dir and dir, (k>1,if_doc=0->flag=0,need newline)(k=1,if_doc>0->
			{
				printf("\n");
			}
			if((i3)&&(flag_dir_doc==0)&&(if_doc))//newline between dor and dir
			{
				printf("\n");//all doc display finishes
				flag_dir_doc=1;
			}

			if(k>=2||Rround==1)
			{
				printf("%s:\n",dir_name[i2]);
			}

			char tmp[MAXNUM][MAXLINE];
			
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
				//lprint(tmp[i4]);
				printf("%s\t",sort_dir[i4]);
			}
			if(i3)
			{
				printf("\n");
				char *tmp_arr[MAXNUM];
				int i5=0;
				for (int i=0;i<i3;i++)
				{
					if(sort_dir[i][0]!='.')
					{
						tmp_arr[i5]=tmp[i];
						i5++;
					}
				}
				
				const int n11=sp_dir(i5,tmp_arr);
				
				char *tmp_dir[MAXNUM];//[i3-n11]all the parameter
				for(int i=n11;i<i5;i++)
				{
					tmp_dir[i-n11]=tmp_arr[i];
				}
				//printf("directory name: ");
				allpt(i5-n11,tmp_dir);
				Rround=1;
				if(i5-n11)PR( tmp_dir,i5-n11, flag_dir0,Rround);
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

