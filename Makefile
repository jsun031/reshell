VPATH=./src/
OPATH=./bin/
objects=shll6comment.o setup.o and_or.o smcln.o
source=$(VPATH)shll6comment.cpp $(VPATH)setup.cpp $(VPATH)and_or.cpp $(VPATH)smcln.cpp
objects2=main.o preop.o lform.o presult.o
source2=$(VPATH)main.cpp $(VPATH)preop.cpp $(VPATH)lform.cpp $(VPATH)presult.cpp
CFLAGS = -ansi -pedantic -Wall -Werror

all : rshell ls

rshell : bin $(objects)
	g++ $(CFLAGS) $(source) -o $(OPATH)rshell
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


ls : bin $(objects2)
	g++ $(CFLAGS) $(source2) -o $(OPATH)ls


main.o : main.cpp
	g++ $(CFLAGS) -c $(VPATH)main.cpp $(VPATH)ls.h -o $(OPATH)main.o

preop.o : preop.cpp 
	g++ $(CFLAGS) -c $(VPATH)preop.cpp $(VPATH)ls.h -o $(OPATH)preop.o
 
lform.o : lform.cpp
	g++ $(CFLAGS) -c $(VPATH)lform.cpp $(VPATH)ls.h -o $(OPATH)lform.o

presult.o : presult.cpp 
	g++ $(CFLAGS) -c $(VPATH)presult.cpp $(VPATH)ls.h -o $(OPATH)presult.o

clean :
	rm -rf bin
