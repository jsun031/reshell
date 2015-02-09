#include "ls.h"

#define print1(x) cout <<((x&S_IFDIR)?"d":"-")<< ((x&S_IRUSR)?"r":"-")<< ((x&S_IWUSR)?"w":"-")<< ((x&S_IXUSR)?"x":"-")\
<< ((x&S_IRGRP)?"r":"-")<< ((x&S_IWGRP)?"w":"-")<< ((x&S_IXGRP)?"x":"-")\
<< ((x&S_IROTH)?"r":"-")<< ((x&S_IWOTH)?"w":"-")<< ((x&S_IXOTH)?"x":"-")
#define print2(x) print1(x.st_mode)//<<" "<<x.st_nlink<<" "
int lpreprint(struct stat s,int mx,int mxlnk)
{
	print2(s);//permission

	char pnk[MAXLINE];
	int dnk=mxlnk;
	char ank[MAXLINE];
	itoa(dnk,ank,10);
	strcpy(pnk," %");
	strcat(pnk,ank);
	strcat(pnk,"d");
	printf(pnk,s.st_nlink);


	struct passwd *passwd;
	passwd = getpwuid (s.st_uid);
	struct group *group;
	group = getgrgid (s.st_gid);
	printf(" %s %s ",passwd->pw_name,group->gr_name);//user name, group name

	char psz[MAXLINE];
	int dsz=mx;
	char asz[MAXLINE];
	itoa(dsz,asz,10);
	strcpy(psz,"%");
	strcat(psz,asz);
	strcat(psz,"ld");
	printf(psz,s.st_size);

	char *p=ctime(&s.st_mtime);//time
	for (int i=4;i<17;i++)
	{
		p[i-4]=p[i];
	}
	p[12]='\0';
	printf(" %s ",p);
	return 0;
}
int lprint(char listname[],int mx,int mxlnk)//print in "-l" format
{
	struct stat s;
	if(stat(listname,&s)==0)
	{
		lpreprint(s,mx,mxlnk);
		return 0;
	}
	else
	{
		perror("stat wrong!/n");
		exit(1);
	}
}

int count(int n)
{
	int i=0;
	while(n>0)
	{
		n=n/10;
		i++;
	}
	return i;
}
int lform(int i3, char *tmp[MAXNUM],char*sort_dir[MAXNUM])
{
	struct stat s[MAXNUM];
	int mxsz=0;
	int mxlnk=0;
	int tmpnum=0;
	for(int i=0;i<i3;i++)
	{
		if(stat(tmp[i],&s[i])==0)
		{
			tmpnum=count(s[i].st_size);
			if(tmpnum>mxsz)
			{
				mxsz=tmpnum;
			}
			tmpnum=count(s[i].st_nlink);
			if(tmpnum>mxlnk)
			{
				mxlnk=tmpnum;
			}
		}
		else
		{
			perror("stat wrong!/n");
			exit(1);
		}		

	}
	for(int i=0;i<i3;i++)
	{
		lprint(tmp[i],mxsz,mxlnk);
		printf("%s\n",sort_dir[i]);
	}
	return 0;
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base)
{
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}
