//
//  DaysOfWeek.hpp
//  Assingment5
//
//  Created by Dawit Tafesse on 4/22/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//

#ifndef DaysOfWeek_h
#define DaysOfWeek_h

#include <iostream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

class DaysOfWeek{
   
    public:
        DaysOfWeek( );
        DaysOfWeek(string d);
        void setDays(string d);
        bool input(istream& ins);
        void output(ostream& outs) const;
        bool isOverlap(const DaysOfWeek& course1) const;
        bool isEqual(const DaysOfWeek& course1) const;
 
    string getDays( ) const;
    
    private:
    
    int TrasnlateDayToItsIndex(const char* d){
        
        
        int index; // error
        
        if((strcmp(d, "M") == 0) || (strcmp(d, "m") == 0)){
            index = 0;
            
        }
        else if((strcmp(d, "T") == 0) || (strcmp(d, "t") == 0)){
            index = 1;
            
        }
        else if((strcmp(d, "W") == 0) || (strcmp(d, "w") == 0)){
            index = 2;
        }
        else if((strcmp(d, "R") == 0) || (strcmp(d, "r") == 0)){
            index = 3;
            
        }
        else if((strcmp(d, "F") == 0) || (strcmp(d, "f") == 0)){
            index = 4;
            
        }
        else if((strcmp(d, "S") == 0) || (strcmp(d, "s") == 0)){
            index = 5;
            
        }
        else if((strcmp(d, "O") == 0) || (strcmp(d, "o") == 0)){ // online
            index = -1;
        }
        else{
            index = -10;
        }
        return index; // it was invalid letter;
    }
 
        bool arr[6];
};

    //Returns true if a and b overlap, false otherwise
    bool operator&&(const DaysOfWeek& a, const DaysOfWeek& b);
    //Returns true if a and b are not equal, false otherwise
    bool operator==(const DaysOfWeek& a, const DaysOfWeek& b);
    //Returns true if a and b are not equal, false otherwise
    bool operator!=(const DaysOfWeek& a, const DaysOfWeek& b);
    //Use the input member funtion to implement stream extraction for DaysOfWeek
    istream& operator>>(istream& ins, DaysOfWeek& d);
    //Use the output member funtion to implement stream insertion for DaysOfWeek
    ostream& operator<<(ostream& outs, const DaysOfWeek& d);


#endif /* DaysOfWeek_h */
