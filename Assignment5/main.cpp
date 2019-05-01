//
//  main.cpp
//  Assingment5
//
//  Created by Dawit Tafesse on 4/11/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "Course.h"

using namespace std;

int getTimeFromString(char* arr){
    int Time;
    if(arr[0] == '0'){
        char temp[1];
        temp[0] = arr[1];
        Time = (int)atol(temp);
        return Time;
        
    }else if(arr[0] == '-'){
        cout << "No negative Time" << endl;
        return -1;
        
    }else
    {
        Time = (int)atol(arr);
        return Time;
    }
}
int getHour(char* str){
    char * pch;
    pch = strtok (str,":");
    
    char* startHour = pch;
    
    int startHourValue;
    startHourValue = getTimeFromString(startHour);
    
    
    return startHourValue;
    
}
int getMinute(char* str){
    char * pch;
    pch = strtok (str,":");
    
    char* startHour = pch;
    char* startMin;
    
    int startHourValue, startMinuteValue = 0;
    startHourValue = getTimeFromString(startHour);
    
    while (pch != NULL)
    {
        pch = strtok (NULL, " ,.-");
        startMin = pch;
        if(startMin != NULL){
            startMinuteValue = getTimeFromString(startMin);
        }
    }
    return startMinuteValue;
    
}
Course performAdd(vector<string> &responseArray){
    
    DaysOfWeek days(responseArray[1]);
    
    char str[6];
    char str2[6];
    char strCopy[6];
    char str2Copy[6];
    
    strcpy(str, responseArray[2].c_str());
    strcpy(str2, responseArray[3].c_str());
    strcpy(strCopy, responseArray[2].c_str());
    strcpy(str2Copy, responseArray[3].c_str());
    
    int startHour, startMin, endHour, endMin;
    
    startHour = getHour(str);
    startMin = getMinute(strCopy);
    endHour = getHour(str2);
    endMin = getMinute(str2Copy);
    
    if(startHour == -1 || startMin == -1 || endHour == -1 || endMin == -1){
        cout << "Entered Negative Time!! Not Allowed, Program will Crash!" << endl;
        
    }
    
    DigitalTime startTime(startHour, startMin);
    DigitalTime endTime(endHour, endMin);
    TimeInterval theTime(startTime, endTime);
    
    Course theCourse(days, theTime, responseArray[4], responseArray[5], responseArray[6]);
    return theCourse;
}
int main(int argc, char** argv){
    
    vector<Course> CourseArray;
    
    string request;
    cout << "Welcome to the schedule maker, make sure to enter a valid entry in SFF Format!" << endl;
    cout << "Enter SFF Format request: " << endl ;
    getline(cin, request);
    
    do{
       
        istringstream iss(request);
        string s;
        vector<string> responseArray;
        while ( getline( iss, s, ' ' ) ) {
            //printf( "`%s'\n", s.c_str() );
            responseArray.push_back(s);
        }
        /*for(int i = 0; i < responseArray.size(); i+=1){
         cout << responseArray[i] << " " ;
         
         }*/
        
        ////////////********* ADD *************
        if(strcmp(responseArray[0].c_str(), "add") == 0){
            
            Course theCourse = performAdd(responseArray);
            CourseArray.push_back(theCourse);
            
        }////////////********* CLEAR *************
        else if(strcmp(responseArray[0].c_str(), "clear") == 0){
            CourseArray.clear();
            
        }////////////********* EXPORT *************
        else if(strcmp(responseArray[0].c_str(), "export") == 0){
            //Validate Schedule
            for(int i = 0; i < CourseArray.size(); i+=1){
                for(int j = i+1; j < CourseArray.size(); j+=1){
                    if(CourseArray[i].isOverlap(CourseArray[j]) == true){
                        cout << "There is an Overalap! " << CourseArray[i].getInstructor() << " is teaching 2 courses at the same time!" << endl;
                    }
                    else if((CourseArray[i].isMatch(CourseArray[j])) == true){
                        cout << "There is a Match! 2 courses have the same course code and section!" << endl;
                    }
                }
            }
            
            string fileNameOut = responseArray[1];
            ofstream outFile;
            
            outFile.open(fileNameOut);
            
            //check for error
            if(outFile.fail()){
                cerr << "Error took place when opening file" << endl;
                exit(1);
            }
            
            for(int i = 0; i < CourseArray.size(); i+=1){
                
                outFile << CourseArray[i].getDaysOfWeek() << " " << CourseArray[i].getTime() << " "  << CourseArray[i].getCourseCode() << " " << CourseArray[i].getSection() << " " <<CourseArray[i].getInstructor() << endl;

            }
            
            outFile.close();
            
        }////////////********* IMPORT *************
        else if(strcmp(responseArray[0].c_str(), "import") == 0){
            string fileNameIn = responseArray[1];
            
            ifstream inFile;
            inFile.open(fileNameIn);
            
            
            //check for error
            if(inFile.fail()){
                cerr << "Error took place when opening file" << endl;
                exit(1);
            }
            
            string line;
            int lineNumber = 0;
            while(inFile.eof() == false){
                getline(inFile, line);
                //inFile >> line; // take current line and set to string line
                cout << line << endl;
                
                istringstream iss2(line);
                string s2;
                vector<string> responseArray2;
                while ( getline( iss2, s2, ' ' ) ) {
                    responseArray2.push_back(s2);
                }
                
                Course theCourse = performAdd(responseArray2);
                CourseArray.push_back(theCourse);
                
                if(responseArray2.size() != 7){
                    cout << "Line " << lineNumber << "is not in SFF Format!!" << endl;
                }
            }
            
            inFile.close();
            
        }////////////********* REMOVE *************
        else if(strcmp(responseArray[0].c_str(), "remove") == 0){
            
            string courseCode = responseArray[1];
            string section = responseArray[2];
            
            for(int i = 0; i < CourseArray.size(); i+=1){
                
                string currentCourseCode = CourseArray[i].getCourseCode();
                if(strcmp(currentCourseCode.c_str(), courseCode.c_str()) == 0){
                    
                    string currentCourseSection = CourseArray[i].getSection();
                    if(strcmp(currentCourseSection.c_str(), section.c_str()) == 0){
                        CourseArray.erase(CourseArray.begin()+i); // erase the i th term
                        cout << "success removing course " << endl;
                    }
                }
            }
            
        }////////////********* VALIDATE *************
        else if(strcmp(responseArray[0].c_str(), "validate") == 0){
            
            for(int i = 0; i < CourseArray.size(); i+=1){
                for(int j = i+1; j < CourseArray.size(); j+=1){
                    if(CourseArray[i].isOverlap(CourseArray[j]) == true){
                        cout << "There is an Overalap! " << CourseArray[i].getInstructor() << " is teaching 2 courses at the same time!" << endl;
                    }
                    else if((CourseArray[i].isMatch(CourseArray[j])) == true){
                        cout << "There is a Match! 2 courses have the same course code and section!" << endl;
                    }
                }
            }
            
        }
        //request = "";
        cout << "Type 'end' to terminator or type valid SFF request: " << endl;
        getline(cin, request);
        //cin >> request;
        
    }while(strcmp(request.c_str(), "end") != 0);
    
    return 0;
}
