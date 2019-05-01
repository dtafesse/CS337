#include <iostream>
using namespace std;


int main() {
  int x = -1;
  int  min, max, current = 0;
  double sum = 0;
  bool First = true;

  while(x<1 || x > 100){
     cout << "Enter the size of data set of integer[0,100]: ";
     cin >> x;
  }
  	
  cout <<"Value 1: " << endl;
  cin >> current;
  sum = sum + current;
  min = current;
  max = current;
  
 for(int i = 2; i <= x; i+=1){  
   cout << "Value"<< i<<": " << endl; 
   cin >> current;
   sum = sum + current;
    if(current < min){
	min = current;
     }
     else if(current > max){
	max = current;
     }
  }
  cout <<"mean is: "<< sum/x << endl;
  cout <<"minimum is: "<<  min << endl;
  cout <<"maximum is: "<< max << endl;
  return 0;
}
