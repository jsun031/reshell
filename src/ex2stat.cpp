#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>

using namespace std;
#define print1(x) cout <<((x&S_IFDIR)?"d":"-")<< ((x&S_IRUSR)?"r":"-")<< ((x&S_IWUSR)?"w":"-")<< ((x&S_IXUSR)?"x":"-")\
<< ((x&S_IRGRP)?"r":"-")<< ((x&S_IWGRP)?"w":"-")<< ((x&S_IXGRP)?"x":"-")\
<< ((x&S_IROTH)?"r":"-")<< ((x&S_IWOTH)?"w":"-")<< ((x&S_IXOTH)?"x":"-")
#define print2(x) print1(x.st_mode)<<" "<<x.st_nlink<<" "
int main()
{
	char listname[]="ex1.cpp";
	struct stat s;
	if(stat(listname,&s)==0)
	{
	cout << oct;
	cout << s.st_mode << endl;
	print2(s);//permission

	struct passwd *passwd;
	passwd = getpwuid (s.st_uid);
	struct group *group;
	group = getgrgid (s.st_gid);
	printf("%s %s %lld ",passwd->pw_name,group->gr_name,  (long long)s.st_size);//user name, group name, size

	char *p=ctime(&s.st_mtime);//time
	for (int i=4;i<17;i++)
	{
		p[i-4]=p[i];
	}
	p[12]='\0';
	printf("%s %s\n",p,listname);
	return 0;
	}
	else
	{
		perror("stat wrong!/n");
		exit(1);
	}
}
