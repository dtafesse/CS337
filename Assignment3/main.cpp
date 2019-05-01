#include "main.h"

using namespace std;

char shift(char c, int offset){
    
    if(isalpha(c)){
        if(isupper(c)){
            c = (((c-65)+offset) % 26) + 65;
        }
        else{
            c = (((c-97)+offset) % 26) + 97;
        }
    }
    return c;
}

int main(int argc, char** argv) {
    
    char* fileNameIn = argv[1];
    char* fileNameOut = argv[2];
    int offset = atoi(argv[3]);

    ifstream inFile;
    ofstream outFile;
    inFile.open(fileNameIn);
    outFile.open(fileNameOut);
    
    //check for error
    if(inFile.fail()){
        cerr << "Error took place when opening file" << endl;
        exit(1);
    }
    if(outFile.fail()){
        cerr << "Error took place when opening file" << endl;
        exit(1);
    }
    if(offset < -25 || offset > 25)
    {
        cerr << "The value of offset was out of range\n";
	exit(1);
    }
    if(offset < 0){
        offset = 26 + offset;  // adding because offset is negtive -> subtracting
    }
    
    string line;
    string message;
    while(getline(inFile, line)){
        
        message = line;
        for(int i = 0; i < line.length(); i+=1){
            message[i] = shift(line[i], offset);
        }
        outFile << message << endl;
    }
    
    inFile.close();
    outFile.close();

    return 0;
}
