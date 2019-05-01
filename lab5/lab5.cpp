#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
    char* temp;
    for(int i = 1; i < argc; i+= 1){
	int minIndex = i;///Selection Sort
        
        for(int j = i; j < argc; j+=1)
        {
            if(strcmp(argv[minIndex], argv[j]) > 0){
                minIndex = j;
            }
        }
        
        temp = argv[i];
        
        argv[i] = argv[minIndex];
        argv[minIndex] = temp;

    }
    for(int i = 1; i < argc; i++){
        cout<< argv[i] << endl;
    }
    return 0;
}
