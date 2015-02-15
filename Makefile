VPATH=./src/
OPATH=./bin/
objects=rshell.o
source=$(VPATH)shll6comment.cpp $(VPATH)setup.cpp $(VPATH)and_or.cpp $(VPATH)smcln.cpp
objects2=ls.o
source2=$(VPATH)main.cpp $(VPATH)preop.cpp $(VPATH)lform.cpp $(VPATH)presult.cpp
CFLAGS = -ansi -pedantic -Wall -Werror

all : rshell ls

rshell : bin $(objects)
	g++ $(CFLAGS) $(source) -o $(OPATH)rshell

ls : bin $(objects2)
	g++ $(CFLAGS) $(source2) -o $(OPATH)ls

bin:
	mkdir bin

rshell.o : $(source)
	g++ $(CFLAGS)  $(source) $(VPATH)rshell.h -o $(OPATH)rshell.o


ls.o : $(sourc2)
	g++ $(CFLAGS)  $(source) $(VPATH)ls.h -o $(OPATH)main.o

clean :
	rm -rf bin
