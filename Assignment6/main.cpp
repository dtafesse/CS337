//
//  main.cpp
//  Assingment 6
//
//  Created by Dawit Tafesse on 5/4/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#include "MySocket.h"
#include <iostream>
using namespace std;

void doprocessing(MyConnection con){
    char* buffer;
    string intro = "Eliza> Hello, and Welcome, What would you like to discuss?\n";

    con.writes(intro);
    while(true){
        
        con.writes("User> ");
        buffer = con.reads(buffer);
        
        string response (buffer);
        string toClient = "Eliza> "+ response;
        con.writes(toClient);
        
    }
}

int main(int argc, char** argv){
    
    int pid;
    
    MySocket sock(atoi(argv[1])); // argv[1] = portNumber
    sock.listens();
    
    while(1){
        MyConnection con = sock.accepts();
        pid = fork();
        
        if (pid < 0) {
            perror("ERROR on fork");
            exit(1);
        }
        
        if (pid == 0) {
            /* This is the client process */
            sock.closes();
            doprocessing(con);
            exit(0);
        }
        else {
            con.closes();
        }
        
    } /* end of while */

}

