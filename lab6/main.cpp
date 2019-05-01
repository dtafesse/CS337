#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char** argv)
{
    double number = 0;
    
    cout << "Enter a double: ";
    cin >> number;
    
    unsigned long* ptr = new unsigned long;
    memcpy( ptr, &number, sizeof(unsigned long) );
    
    unsigned long sign, exponent, mantissas;

    
    sign = *ptr >> 63;
    
    exponent = *ptr & 0x7ff0000000000000;
    exponent >>= 52; // shift to the right 52 bits
    exponent = exponent - 1023;
    
    mantissas = *ptr & 0x000fffffffffffff;
    mantissas = (0x0010000000000000) | mantissas;
    mantissas >>= 1;
    
    while((mantissas & 0x0000000000000001) == 0){
        mantissas >>= 1;
    }
    
    if(sign == 0){
        cout << "sign: +" << endl;
    }
    else
    {
        cout << "sing: -" << endl;
    }
    cout << "Base: 2 (Always)" << endl;
    cout << hex << "Exponent: " << exponent << endl;
    cout << hex << "Mantissa: " << mantissas << endl;
    
}

