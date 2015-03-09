#include "rshell.h"

int main()
{
	char inputBuffer[MAXLINE];
	char s[MAXLINE];
	uid_t userid;
	struct passwd* pwd;
	userid=getuid();
	if(userid==0)
	{
		perror("getuid error!");
		exit(1);
	}
	pwd=getpwuid(userid);
	if(pwd==NULL)
	{
		perror("getpwuid error!");
		exit(1);
	}
	char name[MAXLINE];
	gethostname(name, sizeof(name));
	if(name==NULL)
	{
		perror("gethostname error!");
		exit(1);
	}
	getcwd(s,MAXLINE);
	if(s==NULL)
	{
		perror("getcwd error!");
		exit(1);
	}
	while (1)
	{
        memset(inputBuffer,0,MAXLINE);
		printf("%s@%s:%s->",pwd->pw_name,name,s);
		cin.getline(inputBuffer,MAXLINE);
		smcln(inputBuffer);
	}
	return 0;
}
