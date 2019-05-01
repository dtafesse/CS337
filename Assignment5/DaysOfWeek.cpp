//
//  DaysOfWeek.cpp
//  Assingment5
//
//  Created by Dawit Tafesse on 4/22/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#include "DaysOfWeek.h"

using namespace std;

DaysOfWeek::DaysOfWeek( ){
    // by default No classes are assinged to any days
    for(int i = 0; i < 6; i+=1){
        this->arr[i] = false;
    }
}
DaysOfWeek::DaysOfWeek(string d){
    int index;
    const char *days = d.c_str();
    
    // by default No classes are assinged to any days
    for(int i = 0; i < 6; i+=1){
        this->arr[i] = false;
    }
    
    vector<string> strArr(d.length());
    for(int i = 0; i < d.length(); i +=1){
        strArr[i] = days[i];
        
    }

    for(int i = 0; i < d.length(); i+=1){
        index = this->TrasnlateDayToItsIndex(strArr[i].c_str());
        if(index == -1){
            // online class, reset all days to all "off"
            for(int i = 0; i < 6; i+=1){
                
                this->arr[i] = false;
            }
            break;
        }else if(index == -10){ // errorCode That private method failed
            cout << "There is error with passed arugment. Pass in (M-S, O) only!" << endl;
            break;
        }
        this->arr[index] = true;
    }
}
void DaysOfWeek::setDays(string d){
    int index;
    const char *days = d.c_str();
    
    
    vector<string> strArr(d.length());
    for(int i = 0; i < d.length(); i +=1){
        strArr[i] = days[i];
        
    }
    
    for(int i = 0; i < d.length(); i+=1){
        index = this->TrasnlateDayToItsIndex(strArr[i].c_str());
        if(index == -1){
            // online class, reset all days to all "off"
            for(int i = 0; i < 6; i+=1){
                this->arr[i] = false;
            }
            break;
        }else if(index == -10){ // errorCode That private method failed
            cout << "There is error with passed arugment. Pass in (M-S, O) only!" << endl;
            break;
        }
        this->arr[index] = true;
    }
}
bool DaysOfWeek::input(istream& ins){
    string d;
    ins >> d;
    
    int index;
    const char *days = d.c_str();
    
    vector<string> strArr(d.length());
    for(int i = 0; i < d.length(); i +=1){
        strArr[i] = days[i];
        
    }
    
    for(int i = 0; i < d.length(); i+=1){
        index = this->TrasnlateDayToItsIndex(strArr[i].c_str());
        if(index == -1){
            // online class, reset all days to all "off"
            for(int i = 0; i < 6; i+=1){
                this->arr[i] = false;
            }
            return true;
        }else if(index == -10){ // errorCode That private method failed
            cout << "There is error with passed arugment. Pass in (M-S, O) only!" << endl;
            return false;
        }
        this->arr[index] = true;
    }
    
    return true;
}
void DaysOfWeek::output(ostream& outs) const{
    string days = "";
    
    bool Empty = false;
    for(int i = 0; i < 6; i+=1){
        if(this->arr[i] == true){
            Empty = false;
            break;
        }else{
            Empty = true;
        }
    }
    if(this->arr[0] == true && (Empty == false)){
        days += "M";
    }
    if(this->arr[1] == true && (Empty == false)){
        days += "T";
    }
    if(this->arr[2] == true && (Empty == false)){
        days += "W";
    }
    if(this->arr[3] == true && (Empty == false)){
        days += "R";
    }
    if(this->arr[4] == true && (Empty == false)){
        days += "F";
    }
    if(this->arr[5] == true && (Empty == false)){
        days += "S";
    }
    if(Empty == true){
        days += "O";
    }
    
    outs << days;
}
bool DaysOfWeek::isOverlap(const DaysOfWeek& course1) const{
    for(int i = 0; i < 6; ++i )
    {
        if ((!(this->arr[i] && course1.arr[i])) == false){ // NAND logic, "if both inputs are "true, The output is false" Otherwise, the output is true."
            return true; // at least one match, overlap
        }
    }
    return false; // there is no overlap, recall online classes do not overlap
}
bool DaysOfWeek::isEqual(const DaysOfWeek& course1) const{
    for(int i = 0; i < 6; ++i )
    {
        if (this->arr[i] != course1.arr[i]){ // find the first instance when they are not equal
            return false; // thus they are not equal
        }
    }
    return true; //
}


string DaysOfWeek::getDays( ) const{
    string days = "";
    
    bool Empty = false;
    for(int i = 0; i < 6; i+=1){
        if(this->arr[i] == true){
            Empty = false;
            break;
        }else{
            Empty = true;
        }
    }
    if(this->arr[0] == true && (Empty == false)){
        days += "M";
    }
    if(this->arr[1] == true && (Empty == false)){
        days += "T";
    }
    if(this->arr[2] == true && (Empty == false)){
        days += "W";
    }
    if(this->arr[3] == true && (Empty == false)){
        days += "R";
    }
    if(this->arr[4] == true && (Empty == false)){
        days += "F";
    }
    if(this->arr[5] == true && (Empty == false)){
        days += "S";
    }
    if(Empty == true){
        days += "O";
    }
    
    return days;
}


//Returns true if a and b overlap, false otherwise
bool operator&&(const DaysOfWeek& a, const DaysOfWeek& b){
    return a.isOverlap(b);
}
//Returns true if a and b are equal, false otherwise
bool operator==(const DaysOfWeek& a, const DaysOfWeek& b){
    return a.isEqual(b);
}
//Returns true if a and b are not equal, false otherwise
bool operator!=(const DaysOfWeek& a, const DaysOfWeek& b){
    return !(a.isEqual(b));
}
//Use the input member funtion to implement stream extraction for DaysOfWeek
istream& operator>>(istream& ins, DaysOfWeek& d){
    if(d.input(ins) == false){
        cout << "Error" << endl;
    }
    return ins;
}
//Use the output member funtion to implement stream insertion for DaysOfWeek
ostream& operator<<(ostream& outs, const DaysOfWeek& d){
    d.output(outs);
    return outs;
}
