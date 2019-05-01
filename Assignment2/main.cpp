//
//  main.cpp
//  Assingment2
//
//  Created by Dawit Tafesse on 2/16/17.
//  Copyright © 2017 Dawit Tafesse. All rights reserved.
//
#include "main.h"

using namespace std;


vector<int> shuffle(vector<int> & arr, int n){
    
    srand(time(NULL));
    int x, y = 0;
 
    // initilzie array first
    for(int i = 0; i < n; i +=1){
        arr[i] = i;
        
    }
    
    //shuffle
    for(int i = 0; i < n; i+=1){
        x = rand()%(n-1);
        y = rand()%(n-1);
        
        int temp = arr[x];
        arr[x] = arr[y];
        arr[y] = temp;
    
    }

    return arr;

}


int main() {
    
    
    int n = -1;

    while(n < 10 || n > 100){
        cout << "Enter a number between 10 - 100: ";
        cin >> n;
    }
    
    vector<int> arr(n);
    
   
   // arr = shuffle(arr, n);
    shuffle(arr, n);
    
    int start = arr.front();
    cout << endl << "First Card is: " << start << ", Intital score = 0 "  << endl << endl;
  
   
    string response ;
    char res = 0;
    int score = 0;
    while(arr.size() != 1){ // game ends when there is one card remining
       
        int current = arr.front();
        int next = arr[1];
        
        arr.erase(arr.begin());
        
        while(res != 'H' && res != 'L') {
            cout << "Type H for higher or type L for lower: ";
            cin >> response;
            cout << endl;
            
            res = response.at(0);
        }
        
        if(next > current){
            if(response == "H"){
                score += 1;
                cout << "Correct, score is: " << score << endl;
                cout << "The card("<< next <<") is higher than the previous current(" << current<<"), now new current card is: " << next << endl << endl;
            }
            else {
                score -= 1;
                cout << "Incorrect, score is: " << score << endl;
                cout << "The card("<< next <<") is higher than the previous current(" << current<<"), now new current card is: " << next << endl << endl;
            }
        }
        else{
            if(response == "L") {
                score += 1;
                cout << "Correct, score is: " << score << endl;
                cout << "The card("<< next <<") is lower than the previous current(" << current<<"), now new current card is: " << next << endl << endl;
            }
            else{
                score -= 1;
                cout << "Incorrect, score is: " << score << endl;
                cout << "The card("<< next <<") is not higher than the previous current(" << current<<"), now new current card is: " << next << endl << endl;
            }
        }
        res = 0; //reset our testing variable
    
    }
    cout << "Game over, Final score is: " << score << endl;
    

    return 0;
}
