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
#include "Course.h"

using namespace std;


int getTimeFromString(char* arr){
    int Time;
    if(arr[0] == '0'){
        char temp[1];
        temp[0] = arr[1];
        Time = (int)atol(temp);
        return Time;
        
    }
    Time = (int)atol(arr);
    return Time;
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
int main(int argc, char** argv){

    vector<Course> CourseArray;
    
    if(strcmp(argv[1], "add") == 0){
        
        
        char strCopy[6];
        char str2Copy[6];
        
        strcpy(strCopy, argv[3]);
        strcpy(str2Copy, argv[4]);
        
        int startHour, startMin, endHour, endMin;
        
        startHour = getHour(argv[3]);
        startMin = getMinute(strCopy);
        endHour = getHour(argv[4]);
        endMin = getMinute(str2Copy);
        
        DaysOfWeek days(argv[2]);
        DigitalTime startTime(startHour, startMin);
        DigitalTime endTime(endHour, endMin);
        TimeInterval theTime(startTime, endTime);
        
        /*Course theCourse(days, theTime, argv[5], argv[6], argv[7]);
        CourseArray.push_back(theCourse);
         */
        CourseArray.push_back(Course(days, theTime, argv[5], argv[6], argv[7]));
        cout << CourseArray[0].getDaysOfWeek();
        cout << CourseArray[0].getTime();
        cout << CourseArray[0].getSection();
        cout << CourseArray[0].getInstructor();
        
    }
    
    
    return 0;
    
    
}
