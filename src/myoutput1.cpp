#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#define MAXLINE 256
using namespace std;
class Timer
{
public:
    int start();
    int elapsedWallclockTime (double &);
    int elapsedUserTime (double &);
    int elapsedSystemTime (double &);
    int elapsedTime (double &wc, double &us, double &system);

private:
    rusage old_us_time;
    rusage new_us_time;
    timeval old_wc_time;
    timeval new_wc_time;
};


int
Timer::start()
{
    if (gettimeofday (&this->old_wc_time, 0) == -1
        || getrusage (RUSAGE_SELF, &this->old_us_time) == -1)
        return -1;
    else
        return 0;
}

int
Timer::elapsedWallclockTime (double &wc)
{
    if (gettimeofday (&this->new_wc_time, 0) == -1)
        return -1;
    wc = (this->new_wc_time.tv_sec - this->old_wc_time.tv_sec)
         + (this->new_wc_time.tv_usec - this->old_wc_time.tv_usec) / 1000000.0;
    return 0;
}

int
Timer::elapsedUserTime (double &ut)
{
    if (getrusage (RUSAGE_SELF, &this->new_us_time) == -1)
        return -1;

    ut = (this->new_us_time.ru_utime.tv_sec - this->old_us_time.ru_utime.tv_sec)
        + ((this->new_us_time.ru_utime.tv_usec
            - this->old_us_time.ru_utime.tv_usec) / 1000000.0);
    return 0;
}

int
Timer::elapsedSystemTime (double &st)
{
    if (getrusage (RUSAGE_SELF, &this->new_us_time) == -1)
        return -1;

    st = (this->new_us_time.ru_stime.tv_sec - this->old_us_time.ru_stime.tv_sec)
        + ((this->new_us_time.ru_stime.tv_usec
            - this->old_us_time.ru_stime.tv_usec) / 1000000.0);
    return 0;
}

int
Timer::elapsedTime (double &wallclock, double &user_time, double &system_time)
{
    if (this->elapsedWallclockTime (wallclock) == -1)
        return -1;
    else
        {
            if (getrusage (RUSAGE_SELF, &this->new_us_time) == -1)
        return -1;
            user_time = (this->new_us_time.ru_utime.tv_sec
                - this->old_us_time.ru_utime.tv_sec)
        + ((this->new_us_time.ru_utime.tv_usec
            - this->old_us_time.ru_utime.tv_usec) / 1000000.0);

            system_time = (this->new_us_time.ru_stime.tv_sec
                - this->old_us_time.ru_stime.tv_sec)
        + ((this->new_us_time.ru_stime.tv_usec
            - this->old_us_time.ru_stime.tv_usec) / 1000000.0);

            return 0;
        }
}


int cppio(int argc, char **argv)
{
	std::ofstream outfile (argv[2]);
	char ch;
	char str[MAXLINE];
	int value;
	std::ifstream is(argv[1]);
	char c;
	while(is.get(c))
	{
		ch=c;
		outfile.put(ch);
	}
	is.close();
	return 0;
}

int copen1(int argc,char **argv)
{
	int file2=open(argv[2],O_WRONLY|O_CREAT);
	if(file2<0)
	{
		perror("open file2 error");
		exit(1);
	}
	int file1=open(argv[1],O_RDONLY);
	if(file1<0)
	{
		perror("open file1  error");
		exit(1);
	}
	char str[MAXLINE];
	ssize_t readsize=read(file1,str,1);
	if(readsize<0)
	{
		perror("read error!");
		exit(1);
	}
	while(readsize)
	{
		if(-1==write(file2,str,1))
		{
			perror("write error!");
			exit(1);
		}
		readsize=read(file1,str,1);
	}
	if(readsize<0)
	{
		perror("read error!");
		exit(1);
	}
	if(close(file1)<0)
	{
		perror("close 1 error");
		exit(1);
	}
	if(close(file2)<0)
	{
		perror("close 2 error");
		exit(1);
	}
	return 0;
}

int copen2(int argc,char**argv)
{
	int file2=open(argv[2],O_WRONLY|O_CREAT);
	if(file2<0)
	{
		perror("open file2 error");
		exit(1);
	}
	int file1=open(argv[1],O_RDONLY);
	if(file1<0)
	{
		perror("open file1  error");
		exit(1);
	}
	char str[BUFSIZ];
	//cout<<BUFSIZ<<endl;
	ssize_t readsize=read(file1,str,BUFSIZ);
	//cout <<readsize<<endl;
	if(readsize<0)
	{
		perror("read error!");
		exit(1);
	}
	while(readsize>0)
	{
		if(-1==write(file2,str,readsize))
		{
			perror("write error!");
			exit(1);
		}
		readsize=read(file1,str,BUFSIZ);
		//cout <<readsize<<endl;
	}
	//cout<<"end while"<<endl;
	if(readsize<0)
	{
		perror("read error!");
		exit(1);
	}
	//cout<<"end readsize"<<endl;
	if(close(file1)<0)
	{
		perror("close 1 error");
		exit(1);
	}
	//cout<<"end file1"<<endl;
	if(close(file2)<0)
	{
		perror("close 2 error");
		exit(1);
	}
	//cout<<"end file2"<<endl;
	return 0;
}

int test3methods(int argc, char**argv)
{
	Timer t;
	double eTime;
	double wTime;
	double sTime;
	t.start();
	cppio(argc,argv);
	//copen1(argc,argv);
	//copen2(argc,argv);
	t.elapsedUserTime(eTime);
	cout << "Users time: "<<eTime << endl;
	t.elapsedUserTime(wTime);
	cout << "wallclock time: "<<wTime << endl;
	t.elapsedUserTime(sTime);
	cout << "system time: "<<sTime << endl<<endl;
	Timer t2;
	double eTime2;
	double wTime2;
	double sTime2;
	t2.start();
	//cppio(argc,argv);
	copen1(argc,argv);
	//copen2(argc,argv);
	t2.elapsedUserTime(eTime2);
	cout << "Users time: "<<eTime2 << endl;
	t.elapsedUserTime(wTime2);
	cout << "wallclock time: "<<wTime2 << endl;
	t.elapsedUserTime(sTime2);
	cout << "system time: "<<sTime2 << endl<<endl;
	Timer t3;
	double eTime3;
	double wTime3;
	double sTime3;
	t3.start();
	//cppio(argc,argv);
	//copen1(argc,argv);
	copen2(argc,argv);
	//cout<<"end copen2"<<endl;
	t3.elapsedUserTime(eTime3);
	cout << "Users time: "<<eTime3 << endl;
	t3.elapsedUserTime(wTime3);
	cout << "wallclock time: "<<wTime3 << endl;
	t3.elapsedUserTime(sTime3);
	cout << "system time: "<<sTime3 << endl<<endl;
}

int main(int argc,char**argv)
{
	if(argc>4||argc<3)
	{
		std::cout<<"Wrong number input!"<<std::endl;
		return 1;
	}
	std::ifstream f(argv[2]);
	if (f.good()) {
		std::cout<<"file exits!"<<std::endl;
		f.close();
		return 1;
	} else {
		f.close();
	}
	if(argc==4)
	{
		test3methods(argc,argv);
	}
	if(argc==3)
	{
		copen2( argc, argv);
	}
	return 0;
}
