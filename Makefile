VPATH=./src/
OPATH=./bin/
objects=shll6comment.o setup.o and_or.o smcln.o
source=$(VPATH)shll6comment.cpp $(VPATH)setup.cpp $(VPATH)and_or.cpp $(VPATH)smcln.cpp
CFLAGS = -ansi -pedantic -Wall -Werror

all : rshell

rshell : bin $(objects)
	g++ $(source) -o $(OPATH)rshell
bin: 
	mkdir bin

shll6comment.o : shll6comment.cpp
	g++ $(CFLAGS) -c $(VPATH)shll6comment.cpp $(VPATH)rshell.h -o $(OPATH)shll6comment.o

setup.o : setup.cpp 
	g++ $(CFLAGS) -c $(VPATH)setup.cpp -o $(OPATH)setup.o
 
and_or.o : and_or.cpp
	g++ $(CFLAGS) -c $(VPATH)and_or.cpp $(VPATH)rshell.h -o $(OPATH)and_or.o

smcln.o : smcln.cpp 
	g++ $(CFLAGS) -c $(VPATH)smcln.cpp -o $(OPATH)smcln.o

clean :
	rm -rf bin
