#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#define MAXLINE 80

using namespace std;

int and_or(char* inputBuffer);

int pipesetup(char inputBuffer[]);

int exe(char *input[MAXLINE],int num);

int smcln(char inputBuffer[]);
