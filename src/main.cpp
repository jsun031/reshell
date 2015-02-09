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
		strcpy(listnamsb[i],listname[i]);
		listname[i]=listnamesb[i];
	}
	allpt(k,listname);
	
	char doc_namesb[MAXNUM][MAXLINE];
	const int n1=sp_dir(k,listname);
	char *doc_name[MAXNUM];//n1 documents
	for(int i=0;i<n1;i++)
	{
		strcpy(doc_namesb[i],listname[i]);
		doc_name[i]=doc_namesb[i];
	}
	//printf("document name: ");
	allpt(n1, doc_name);
	
	char dir_namesb[MAXNUM][MAXLINE];
	char *dir_name[MAXNUM];//[k-n1]all the parameter
	for(int i=n1;i<k;i++)
	{
		strcpy(dir_namesb[i-n1],listname[i]);
		dir_name[i-n1]=dir_namesb[i-n1];
	}
	//printf("directory name: ");
	allpt(k-n1,dir_name);

	int flag_dir_doc=0;
	if(R==0)
	{
		if(l==0)
		{
			if(a==1)
			{
				if(n1>1)mysort(doc_name,n1);
				allpt(n1,doc_name);
				for (int i2=0;i2<n1;i2++)	
				{
						printf("%s\t",doc_name[i2]);
				}
				if(n1)//end of doc
				{
					printf("\n");//all doc display finishes
				}

				
				if(k-n1>1)mysort(dir_name,k-n1);
				allpt(k-n1,dir_name);
				
				for (int i2=0;i2<k-n1;i2++)
				{
					DIR *dirptr = NULL;
					struct dirent *entry;
					char *sort_dir[MAXNUM];
					char sort_dirsb[MAXNUM][MAXLINE];
					
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
							strcpy(sort_dirsb[i3],entry->d_name);
							sort_dir[i3]=sort_dirsb[i3];
							i3++;
							//printf("%s\t", entry->d_name);
						}
						if((i3)&&(n1)&&(flag_dir_doc==0))//newline between dor and dir
						{
							printf("\n");//all doc display finishes
							flag_dir_doc=1;
						}
						if(k>=2)
						{
							printf("%s:\n",dir_name[i2]);
						}
						if(i3>1)mysort(sort_dir,i3);
						for(int i4=0;i4<i3;i4++)
						{
							printf("%s\t",sort_dir[i4]);
						}
						if(i2<k-n1-1)
						{
							printf("\n\n");
						}
						else
						{
							printf("\n");
						}
						if(closedir(dirptr)!=0)
						{
							perror("closedir error!\n"); 
							exit(1);
						}//error check
					}
				}				
			}
			else if(a==0)
			{
				if(n1>1)mysort(doc_name,n1);
				allpt(n1,doc_name);
				int if_doc=0;//if doc is display
				for (int i2=0;i2<n1;i2++)	
				{
					if((doc_name[i2][0]!='.')||((doc_name[i2][0]=='.') &&( doc_name[i2][1]=='/') ))
					{
						printf("%s\t", doc_name[i2]);
						if_doc++;
					}
					else
					{
						continue;
					}
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
					char *sort_dir[MAXNUM];
					char sort_dirsb[MAXNUM][MAXLINE];
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
								strcpy(sort_dirsb[i3],entry->d_name);
								sort_dir[i3]=sort_dirsb[i3];
								i3++;
							}							
							//printf("%s\t", entry->d_name);
						}
						if(i3>1)mysort(sort_dir,i3);

						if((k-n1>1)&&(i3))//newline between dir and dir
						{
							printf("\n");
						}
						if((i3)&&(flag_dir_doc==0)&&(if_doc))//newline between dor and dir
						{
							printf("\n");//all doc display finishes
							flag_dir_doc=1;
						}

						
						if(k>=2)
						{
							printf("%s:\n",dir_name[i2]);
						}
						for(int i4=0;i4<i3;i4++)
						{
							printf("%s\t",sort_dir[i4]);
						}
						if(i3)printf("\n");//new line after sort_dir
						
		
						if(closedir(dirptr)!=0)
						{
							perror("closedir error!\n"); 
							exit(1);
						}//error check
					}
				}				
			}
			else//a!=1&&a!=0, should not exist
			{
				printf("-a error!\n");
				exit(1);
			}
		}
		else if(l==1)
		{	
			if(a==1)
			{
				if(n1>1)mysort(doc_name,n1);
				allpt(n1,doc_name);

				char*tmpdoc[MAXNUM];
				int if_doc=0;//if doc is display
				for (int i2=0;i2<n1;i2++)	
				{
					//if((doc_name[i2][0]!='.')||((doc_name[i2][0]=='.') &&( doc_name[i2][1]=='/') ))
					//{
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
					char *sort_dir[MAXNUM];
					char sort_dirsb[MAXNUM][MAXLINE];
				
					
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
								strcpy(sort_dirsb[i3],entry->d_name);
								sort_dir[i3]=sort_dirsb[i3];
								i3++;
							//}							
							//printf("%s\t", entry->d_name);
						}
						if(i3>1)mysort(sort_dir,i3);
						if((k-n1>1)&&(i3))//newline between dir and dir
						{
							printf("\n");
						}
						if((i3)&&(flag_dir_doc==0)&&(if_doc))//newline between dor and dir
						{
							printf("\n");//all doc display finishes
							flag_dir_doc=1;
						}

						if(k>=2)
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
						
						
						if(closedir(dirptr)!=0)
						{
							perror("closedir error!\n"); 
							exit(1);
						}//error check
					}

				}	
				
			}
			else if(a==0)//l=1,R=0
			{
			
				if(n1>1)mysort(doc_name,n1);
				allpt(n1,doc_name);

				char*tmpdoc[MAXNUM];
				int if_doc=0;//if doc is display
				for (int i2=0;i2<n1;i2++)	
				{
					if((doc_name[i2][0]!='.')||((doc_name[i2][0]=='.') &&( doc_name[i2][1]=='/') ))
					{
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
					//P1Dir_a(listname[i2]);
					DIR *dirptr = NULL;
					struct dirent *entry;
					char *sort_dir[MAXNUM];
					
					char sort_dirsb[MAXNUM][MAXLINE];
					
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
								strcpy(sort_dirsb[i3],entry->d_name);
								sort_dir[i3]=sort_dirsb[i3];
								i3++;
							}							
							//printf("%s\t", entry->d_name);
						}
						if(i3>1)mysort(sort_dir,i3);

						if((k-n1>1)&&(i3))//newline between dir and dir
						{
							printf("\n");
						}
						if((i3)&&(flag_dir_doc==0)&&(if_doc))//newline between dor and dir
						{
							printf("\n");//all doc display finishes
							flag_dir_doc=1;
						}

						if(k>=2)
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
											
						if(closedir(dirptr)!=0)
						{
							perror("closedir error!\n"); 
							exit(1);
						}//error check
					}
				/*for (int i2=0;i2<k;i2++)
				{
					P1Dir_l(listname[i2]);
				}*/
				}
			}
			else//a!=1&&a!=0, should not exist
			{
				printf("-a error!\n");
				exit(1);
			}
		}
		
	}
	else if(R==1)
	{
		int Rround=0;
		if(l==1)
		{	
			if(a==1)
			{
				
				PR_al(listname, k,flag_dir0,Rround);
			}
			else if(a==0)
			{
				PR_l(listname, k,flag_dir0,Rround);
			}
			else //a!=0 && a!=1, should not exist
			{
				printf("-a error!\n");
				exit(1);
			}
		}
		else if (l==0)
		{
			if(a==1)
			{
				PR_a( listname, k,flag_dir0,Rround);
			}
			else if(a==0)
			{
				PR(listname, k,flag_dir0,Rround);
			}
			else //a!=0 && a!=1, should not exist
			{
				printf("-a error!\n");
				exit(1);
			}
		}
	}
	//printf("\n");
	//else if(R==0
	//PrintOneDirname(listname[0]);
	return 0;
}
