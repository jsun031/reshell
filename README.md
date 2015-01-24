# rshell

##Overview

rshell is a simple shell. It works almost as bash. It could deal with most bash functions such as ls, pwd and ps, except cd.

It uses fork() to generate child process. In child process, execvp() is used to call functions. In the parent process, waitpid is used to end the child process.

It could deal with commands with semicolon, && and ||.

##Install

To install it, you need a linux system and knowbasic github command. Supposeyou have already initiate github on your computer, then you need to git clone the src directory and Makefile document.

Then, you type in "make" to set it up and type "./bin/rshell" to run it.

##How to use it

It just looks like bash, and you could type any common commands except cd.

The identifier shown on the screen is "command->".

##Command size

I set maximum input size to be 80. You can change it to go to directory src and find MAXLINE in head docoment, and then set a number you like.

##How to unistall

In the directory you git clone, type "make clean" and then delete directory src and Makefile.

##Issue\Bugs\Limitations

1. It could accept & or |. In additon, &&& or  ||| works as && or ||, which is different form bash.

2. It could not deal with cd command.

3. If you type more than 80 characteristics, it would loop forever. Please press Ctrl+c to stop. If you have to do that, you could change input command size follow instruction above.

4. If you would like to quit, just type "exit". "exit" would not work with blank, table, semicolon, && or ||.

5. Press table would fill name automatically.

6. Up down left or right could not be used.
