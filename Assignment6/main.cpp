//
//  main.cpp
//  Assingment 6
//
//  Created by Dawit Tafesse on 5/4/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#include "MySocket.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct topic{
    string topic_name;
    vector<string> list;
};

void doprocessing(MyConnection con){
    //  srand (time(NULL));
    
    topic love, hate, life, Relationship, Work, Health;
    love.topic_name = "love";
    hate.topic_name = "hate";
    life.topic_name = "life";
    Relationship.topic_name = "relationship";
    Work.topic_name = "work";
    Health.topic_name = "health";
    
    love.list.push_back("Are you in love?");
    love.list.push_back("What do you love?");
    love.list.push_back("What's love got to do, got to do with it?");
    love.list.push_back("Are you dating?");
    love.list.push_back("Where do you think this feeling come from?");
    love.list.push_back("What causes these feelings to arise?");
    
    hate.list.push_back("Why do you hate?");
    hate.list.push_back("Are you a narcissist?");
    hate.list.push_back("Where do you think this feeling come from?");
    hate.list.push_back("What causes these feelings to arise?");
    hate.list.push_back("Are you mad at me?");
    hate.list.push_back("Do you only hate specific people?");
    
    life.list.push_back("Is life worth living?");
    life.list.push_back("What is the meaning of life to you?");
    life.list.push_back("What would give your life more meaning?");
    life.list.push_back("What would you change in your life?");
    life.list.push_back("What is your social life like?");
    life.list.push_back("Where do you work/ go to school?");
    
    Relationship.list.push_back("Is there someone you should spend more time with?");
    Relationship.list.push_back("Is there someone you should spend less time with?");
    Relationship.list.push_back("How do you really feel about your mom? ");
    Relationship.list.push_back("What kind of upbringing did you have?");
    Relationship.list.push_back("What are your earliest childhood recollections?");
    Relationship.list.push_back ("How often do you drink alcohol? How much?");
    
    Work.list.push_back("Should you try to find better work?");
    Work.list.push_back("Should you devote more or less effort at work?");
    Work.list.push_back("Should you change how you behave at work?");
    Work.list.push_back("How often do you eat?");
    Work.list.push_back("How often do you drink alcohol? How much?");
    Work.list.push_back("Do you do any drugs? Which and how often? What medications do you take?");
    
    Health.list.push_back("Do you want to lose weight or accept yourself as-is? ");
    Health.list.push_back("Should you exercise more? Less? Differently?");
    Health.list.push_back("Does your body image define you as a person?");
    Health.list.push_back("Do you want to lose weight?");
    Health.list.push_back("Do you accept yourself as-is?");
    Health.list.push_back("Should you exercise more? Less? Differently?");
    
    
    vector<topic> All_Topic;
    All_Topic.push_back(love);
    All_Topic.push_back(hate);
    All_Topic.push_back(life);
    All_Topic.push_back(Relationship);
    All_Topic.push_back(Work);
    All_Topic.push_back(Health);
    
    char* buffer;
    string intro = "Eliza> Hello, and Welcome, What would you like to discuss? If you want to quit, just close the program\n";
    con.writes(intro);
    
    
    vector<string> ResponseArray;
    string delimiter = " ";
    size_t pos = 0;
    string token;
    string toClient;
    int randomNum = 0;
    bool found = false;
    
    while(true){
        
        buffer = con.reads(buffer);
        printf("Here is the message: %s\n",buffer);
        
        string response (buffer);
        transform(response.begin(), response.end(), response.begin(), ::tolower);
        
        //string toClient = "Eliza> "+ response;
        
        while ((pos = response.find(delimiter)) != string::npos) { // splits up response by " " as an input to an array
            token = response.substr(0, pos);
            ResponseArray.push_back(token);
            response.erase(0, pos + delimiter.length());
        }
        ResponseArray.push_back(response.substr(0, string::npos)); //push last remaining substring       
        //special condition the response was only one word
        if(ResponseArray.size() == 1){
            for(int i = 0; i < All_Topic.size(); i+=1){
			
		 if(strcmp(All_Topic[i].topic_name.c_str(), ResponseArray[0].c_str()) == 0){
		    randomNum = rand() % 6; // generates a num between 0-2
                    toClient = All_Topic[i].list[randomNum] +"\n";
                    found = true;
                }
            }
        }//end special condtion
        
        else{
            for(int i = 0; i < All_Topic.size() && !found; i+=1){
                
                for(int j = 0; j < ResponseArray.size() && !found; j+=1){
                    if(strcmp(All_Topic[i].topic_name.c_str(), ResponseArray[j].c_str()) == 0){
                        randomNum = rand() % 6; // generates a num between 0-2
                        toClient = All_Topic[i].list[randomNum] +"\n";
                        found = true;
                    }
                }
            }
        }
            if(found == true){
            con.writes(toClient);
            ResponseArray.clear();
            found = false;
        }
        else{
            con.writes("Tell me more\n");
            ResponseArray.clear();
            found = false;
        }
    }
}
int main(int argc, char** argv){
    srand (time(NULL));
    
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


