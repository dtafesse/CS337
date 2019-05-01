//
//  Course.cpp
//  Assingment5
//
//  Created by Dawit Tafesse on 4/22/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#include "Course.h"

using namespace std;

Course::Course(DaysOfWeek theDays, TimeInterval theTime, string TheCourseCode, string TheSection, string TheInstructor){
    
    this->courseCode = TheCourseCode;
    this->section = TheSection;
    this->instructor = TheInstructor;
    this->days = theDays;
    this->time = theTime;
}
bool Course::isOverlap(const Course& course1) const{
    
    if(strcmp((this->getInstructor()).c_str(), (course1.getInstructor()).c_str()) == 0){
        if(this->getTime()&& course1.getTime()){
            return true;
        }
    }
    return false;
}
bool Course::isMatch(const Course& course1) const{
    if(strcmp((this->getCourseCode()).c_str(), (course1.getCourseCode()).c_str()) == 0){
        if(strcmp((this->getSection()).c_str(), (course1.getSection()).c_str()) == 0){
            return true;
        }
    }
    return false;
}

string Course::getCourseCode() const{
    return this->courseCode;
}
string Course::getSection() const{
    return this->section;
}
string Course::getInstructor() const{
    return this->instructor;
}
DaysOfWeek Course::getDaysOfWeek() const{
    return this->days;
}
TimeInterval Course::getTime() const{
    return this->time;
}

//Returns true if a and b overlap, false otherwise
bool operator&&(const Course& a, const Course& b){
    if(a.isOverlap(b)){
        return true;
    }
    return false;
}
//Returns true if a and b are a Match, false otherwise
bool operator==(const Course& a, const Course& b){
    if(a.isMatch(b)){
        return true;
    }
    return false;
}
