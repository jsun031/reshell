#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <algorithm>
#define MAXLINE 2048
#define MAXNUM 256

using namespace std;
bool cmp_dot(char a[], char b[]);
bool if_all_dot(char a[]);
char* convert(char a[]);//remain only a~z and 0~9
bool compare( char *a, char *b);//sort alphabetically
void mysort(char *list[], int num);
int setaprt(int argc,char**argv);
void allpt(int argc,char **argv);
int sp_dir(int argc,char**argv);

#define print1(x) cout <<((x&S_IFDIR)?"d":"-")<< ((x&S_IRUSR)?"r":"-")<< ((x&S_IWUSR)?"w":"-")<< ((x&S_IXUSR)?"x":"-")\
<< ((x&S_IRGRP)?"r":"-")<< ((x&S_IWGRP)?"w":"-")<< ((x&S_IXGRP)?"x":"-")\
<< ((x&S_IROTH)?"r":"-")<< ((x&S_IWOTH)?"w":"-")<< ((x&S_IXOTH)?"x":"-")
#define print2(x) print1(x.st_mode)//<<" "<<x.st_nlink<<" "

int lpreprint(struct stat s,int mx,int mxlnk);
int lprint(char listname[],int mx,int mxlnk);//print in "-l" format
int count(int n);
int lform(int i3, char *tmp[MAXNUM],char*sort_dir[MAXNUM]);
char* itoa(int value, char* result, int base);

int Print_result(char *listname[MAXNUM],int k,int flag_dir0,int Rround,int a, int R, int l,int flag_dir_doc=0);
