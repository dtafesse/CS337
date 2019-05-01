#include "MySocket.h"

using namespace std;

MySocket::MySocket(){
    perror("must construct with fd");
    exit(-1);
}
//MySocket::MySocket(short p):portNumber(p)
MySocket::MySocket(short p){
    this->socketFD = socket(AF_INET, SOCK_STREAM, 0);
    
    if(this->socketFD < 0){
        perror("Error opening socket");
        exit(1);
    }
    
    /* Initialize socket structure */
    bzero((char*) &(this->sock), sizeof(this->sock));
    this->portNumber = p;
    
    this->sock.sin_family = AF_INET;
    this->sock.sin_addr.s_addr = INADDR_ANY;
    this->sock.sin_port = htons(this->portNumber);
    
    
    /* Now bind the host address using bind() call.*/
    if (bind(this->socketFD, (struct sockaddr *) &this->sock, sizeof(this->sock)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    
}
MyConnection::MyConnection(){
    perror("must construct with fd");
    exit(-1);
    
}
//MyConnection::MyConnection(int fd):connectionFD(fd){
MyConnection::MyConnection(int fd){
    this->connectionFD = fd;
}

//using pointers, must write =, copy, destructor
MySocket& MySocket::operator=(MySocket& m){
    
    if(this != &m){
        this->sock = m.sock;
        this->cli_addr = m.cli_addr;
        this->hPtr = m.hPtr;
        this->socketFD = m.socketFD;
        this->portNumber = m.portNumber;
        this->clien= m.clien;
        
        //char sysHost[MAXHOSTNAME+1];
        memcpy(this->sysHost,0, (MAXHOSTNAME+1)); // clear orignal char Array first then copy
        memcpy(this->sysHost, m.sysHost, (MAXHOSTNAME+1));
    }
    return *this;
}
MySocket::MySocket(const MySocket& newSocket){
    this->sock = newSocket.sock;
    this->cli_addr = newSocket.cli_addr;
    this->hPtr = newSocket.hPtr;
    this->socketFD = newSocket.socketFD;
    this->portNumber = newSocket.portNumber;
    this->clien= newSocket.clien;
    
    //char sysHost[MAXHOSTNAME+1];
    memcpy(this->sysHost,0, (MAXHOSTNAME+1)); // clear orignal char Array first then copy
    memcpy(this->sysHost, newSocket.sysHost, (MAXHOSTNAME+1));
    
}
MySocket::~MySocket(){
  
    delete this->hPtr;
}

char* MyConnection::reads(char *buffer){
    //char buffer[256];
    buffer = new char[256];
    bzero(buffer,256);
    int num = read(this->connectionFD,buffer,255);
    if (num < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    return buffer;
}

int MyConnection::writes(string word){
    char* buf = new char[word.length()+1];
    bzero(buf, word.length()+1);
    memcpy(buf, word.c_str(), word.length()+1); 
   
    int n = write(this->connectionFD,buf,word.length());
    if (n < 0) {
        perror("ERROR Writing from socket");
        exit(1);
    }
    
    delete[] buf;
    
    return n;
}

int MySocket::listens(){
    
    int val = listen((this->socketFD), 5);
    this->clien = sizeof(this->cli_addr);
    
    return val;
}
MyConnection MySocket::accepts(){
    int newsocketfd = accept(this->socketFD, (struct sockaddr *) &this->cli_addr, &this->clien);
    if (newsocketfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    MyConnection myCon(newsocketfd);
    return myCon;
}
void MySocket::closes(){
    close(this->socketFD);
}
void MyConnection::closes(){
    close(this->connectionFD);
}

MyConnection& operator<<(MyConnection& me, const string& s){
    char* copy;
    strcpy(copy,s.c_str());
    me.reads(copy);
    return me;
}
MyConnection& operator>>(MyConnection& me, const string& s){
    string copy(s);
    me.writes(copy);
    return me;
}
