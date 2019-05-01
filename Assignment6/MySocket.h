#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
//#include <iostream>
#include <netinet/ip.h>
#include <string.h>
#include <string>
using namespace std;
#ifndef MYSOCKET
#define MYSOCKET
const int MAXHOSTNAME=255;

class MyConnection
{
private:
    int connectionFD;
    
public:
    MyConnection(); //print error, exit(-1); must construct with fd
    MyConnection(int fd);
    char* reads(char*);
    int writes(string);
    void closes(); //close the connection
    int getconnectionFD(){
        return connectionFD;
    }
};


class MySocket
{
private:
    
    char sysHost[MAXHOSTNAME+1];

    struct  sockaddr_in sock, cli_addr;
    struct hostent* hPtr;
    int socketFD;
    int portNumber;
    unsigned int clien;
    
public:
    MySocket(); //print error, exit(-1); must construct with port #
    MySocket(short portNumber);
    //using pointers, must write =, copy, destructor
    MySocket& operator=(MySocket&);
    MySocket(const MySocket&);
    ~MySocket();
    int listens();
    MyConnection accepts();
    void closes();
};


MyConnection& operator<<(MyConnection&, const string&);
MyConnection& operator>>(MyConnection&, const string&);
#endif
