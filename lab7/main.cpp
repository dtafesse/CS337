#include <algorithm>
#include "main.h"
using namespace std;

const int SIZE = 26;

void printArray(char* letters, long* occurences){
    for(int i = 0; i < SIZE; ++i){
        if(occurences[i] != 0){
            cout << letters[i] << ": " << occurences[i] << endl;
        }
    }
}
void sort(char* letters, long* occurences){
    
    long temp = 0;
    char let;
    
    for(int i=0; i < SIZE; i++){
        for(int j = 1; j < (SIZE-i); j++){
            if(occurences[j-1] < occurences[j]){
                //swap elements
                temp = occurences[j-1];
                occurences[j-1] = occurences[j];
                occurences[j] = temp;
                
                let = letters[j-1];
                letters[j-1] = letters[j];
                letters[j] = let;
                
            }
        }
    }
    
}
void readText(char* letters, long* occurences){
    
    
    char input[1024];
    
    
    int i,j=0;
    
    cout<<"Enter the cypher text: ";
    gets(input);
    
    
    // remove all spaces
    for(i=0;input[i]!='\0';++i)
    {
        if(input[i]!=' ')
            input[j++]=input[i];
    }
    input[j]='\0';
    
    // change all to lower case
    int z = 0;
    char temp;
    
    while(input[z] != '\0'){
        temp = input[z];
        input[z] = tolower(temp);
        z++;
    }
    
    // fill occurences
    for(int i = 0; input[i] != '\0'; ++i){
        for(int j = 0; letters[j] != '\0'; ++j){
            if(letters[j] == input[i]){
                occurences[j] = occurences[j]+1;
            }
        }
    }
    
    sort(letters,occurences);
    printArray(letters,occurences);
    
}

int main(int argc, const char * argv[]) {
    
    char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    
    long* count = new long[SIZE];
    for(int i = 0; i < SIZE; i+=1){
        count[i] = 0;
    }
    
    readText(letters, count);
    
    
    return 0;
}

