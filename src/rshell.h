#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#define MAXLINE 80

using namespace std;

int and_or(char* inputBuffer);

int setup(char inputBuffer[]);

int smcln(char inputBuffer[]);
