//
//  dtime.cpp
//  Assingment5
//
//  Created by Dawit Tafesse on 4/11/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#include "digtalTime.h"

using namespace std;

//Returns true if time1 and host represent the same time;
//otherwise, returns false.
bool DigitalTime::isEqual(const DigitalTime& time1) const{
    
    if((this->getHour() == time1.getHour()) && (this->getMinute() == time1.getMinute())){
        return true;
    }
    return false;

}

//Returns true if host is strictly less than time1;
//otherwise, returns false.
bool DigitalTime::isLess(const DigitalTime& time1) const{
    if((this->getHour() < time1.getHour())){
        return true;
        
    }
    else if((this->getHour() == time1.getHour())){
        if(this->getMinute() < time1.getMinute()){
            return true;
        }
    }
    return false;
}

//Precondition: 0 <= the_hour <= 23 and 0 <= the_minute <= 59.
//Initializes the time value to the_hour and the_minute.
DigitalTime::DigitalTime(int the_hour, int the_minute){
    if((the_hour >= 0) && (the_hour <= 23) && (the_minute >= 0) && (the_minute <= 59)){
        this->hour = the_hour;
        this->minute = the_minute;
    }else{
        cout << "Not a valid Time" << endl;
    }

}

//Initializes the time value to 0:00 (which is midnight).
DigitalTime::DigitalTime(){
    this->hour = 0;
    this->minute = 0;
}

//Reads a white-space delimited token from ins. If the token is of the form
//hh:mm where hh is an integer from 0 to 23 (inclusive) and mm is an integer
//from 0 to 59 (inclusive), host is set to these values and the function returns true.
//Otherwise host is left unchanged and the function returns false.
//Precondition: If ins is a file input stream, then ins has already been
//connected to a file.
bool DigitalTime::input(istream& ins){
    if((this->getHour() >= 0) && (this->getHour() <= 23) &&
       (this->getMinute() >= 0) && (this->getMinute() <= 59)){
       
        ins >> this->hour >> this->minute;
        return true;
    }
    return false;
}

//Outputs digital time in the form hour:minute
//Precondition: If outs is a file output stream, then outs has already been
//connected to a file.
void DigitalTime::output(ostream& outs) const{
    
    outs << this->hour << ":" << this->minute;
}

int DigitalTime::getHour() const{
    return this->hour;
}
int DigitalTime::getMinute() const{
    return this->minute;
}
//If <hour>:<minute> is valid, the digitalTime is set to that value. If either hour
//or minute is not valid, the host object is unchanged.
void DigitalTime::set(int hour, int minute){
    
    if((hour >= 0) && (hour <= 23) && (minute >= 0) && (minute <= 59)){
        this->hour = hour;
        this->minute = minute;
    }
}

//Use the member functions isEqual and isLess to implement each of the operators above.
bool operator<(const DigitalTime& a, const DigitalTime& b){
    if(a.isLess(b)){
        return true;
    }
    return false;
}
bool operator>(const DigitalTime& a, const DigitalTime& b){
    if(!(a.isLess(b))){
        return true;
    }
    return false;
}
bool operator<=(const DigitalTime& a, const DigitalTime& b){
    if(a.isLess(b) || a.isEqual(b)){
        return true;
    }
    return false;
}
bool operator>=(const DigitalTime& a, const DigitalTime& b){
    if(!(a.isLess(b) || a.isEqual(b))){
        return true;
    }
    return false;
}
bool operator==(const DigitalTime& a, const DigitalTime& b){
    if(a.isEqual(b)){
        return true;
    }
    return false;
}
bool operator!=(const DigitalTime& a, const DigitalTime& b){
    if(!(a.isEqual(b))){
        return true;
    }
    return false;
}

//Use the input member funtion to implement stream extraction for DigitalTime
istream& operator>>(istream& ins, DigitalTime& d){
    if(d.input(ins) == false){
        cout << "Error" << endl;
    }
    return ins;
}
//Use the output member funtion to implement stream insertion for DigitalTime
ostream& operator<<(ostream& outs, const DigitalTime& d){
    d.output(outs);
    return outs;
}


