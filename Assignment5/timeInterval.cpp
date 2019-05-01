//
//  timeInterval.cpp
//  Assingment5
//
//  Created by Dawit Tafesse on 4/11/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#include "timeInterval.h"

using namespace std;

//Initializes the interval to [0:00, 0:00].
TimeInterval::TimeInterval( ){
    this->startTime.set(0, 0);
    this->endTime.set(0, 0);

}

//Initializes the interval to [a, b], if a <= b. Otherwise intialize to [0:00, 0:00]
TimeInterval::TimeInterval(const DigitalTime& a, const DigitalTime& b){
    if(a<=b){
        this->startTime.set(a.getHour(), a.getMinute());
        this->endTime.set(b.getHour(), b.getMinute());
    }
    else{
        this->startTime.set(0, 0);
        this->endTime.set(0, 0);
    }
}

//Initializes the interval to [a, b], if a <= b. Otherwise leave host unchanged
void TimeInterval::setInterval(const DigitalTime& a, const DigitalTime& b){
    if(a<=b){
        this->startTime.set(a.getHour(), a.getMinute());
        this->endTime.set(b.getHour(), b.getMinute());
    }
}

DigitalTime TimeInterval::getStart() const{
    return this->startTime;
}
DigitalTime TimeInterval::getEnd() const{
    return this->endTime;
}

//Outputs the interval in the form a - b. For example, 9:30 - 10:45
//Precondition: If outs is a file output stream, then outs has already been
//connected to a file.
void TimeInterval::output(ostream& outs) const{
    DigitalTime start = this->getStart();
    DigitalTime end = this->getEnd();


    outs << start.getHour() << ":" << start.getMinute() << "-"
    << end.getHour() << ":" << end.getMinute();

}
//Returns true if a and b overlap, false otherwise
bool operator&&(const TimeInterval& a, const TimeInterval& b){
    
    if((a.getStart() <= b.getEnd()) && (a.getEnd() >= b.getStart())){
        return true;
    }
    return false;
}

//Use the output member funtion to implement stream insertion for TimeInterval
ostream& operator<<(ostream& outs, const TimeInterval& d){
    d.output(outs);
    return outs;
}

