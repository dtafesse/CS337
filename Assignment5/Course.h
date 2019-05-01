//
//  Course.hpp
//  Assingment5
//
//  Created by Dawit Tafesse on 4/22/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#ifndef Course_h
#define Course_h

#include <cstring>
#include <iostream>
#include "DaysOfWeek.h"
#include "timeInterval.h"
using namespace std;

class Course{
    
    public:
        Course(DaysOfWeek theDays, TimeInterval theTime, string TheCourseCode, string TheSection, string TheInstructor);
        bool isOverlap(const Course& course1) const;
        bool isMatch(const Course& course1) const;
    
    string getCourseCode() const;
    string getSection() const;
    string getInstructor() const;
    DaysOfWeek getDaysOfWeek() const;
    TimeInterval getTime() const;
  
    private:
        string courseCode;
        string section;
        string instructor;
        DaysOfWeek days;
        TimeInterval time;
};

    //Returns true if a and b overlap, false otherwise
    bool operator&&(const Course& a, const Course& b);
    //Returns true if a and b are a Match, false otherwise
    bool operator==(const Course& a, const Course& b);

#endif /* Course_hpp */
