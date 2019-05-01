#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <pwd.h>
#include <stdio.h>

using namespace std;

void premissions( mode_t mode){
    //Owner
    if(mode & S_IRUSR) cout << "r" ;
    else cout << "-";
    if(mode & S_IWUSR) cout << "w";
    else cout << "-";
    if(mode & S_IXUSR) cout << "e";
    else cout << "-";
    //Group
    if(mode & S_IRGRP) cout << "r";
    else cout << "-";
    if(mode & S_IWGRP) cout << "w";
    else cout << "-";
    if(mode & S_IXGRP) cout << "e";
    else cout << "-";
    // Others
    if(mode & S_IROTH) cout << "r";
    else cout << "-";
    if(mode & S_IWOTH) cout << "w";
    else cout << "-";
    if(mode & S_IXOTH) cout << "e";
    else cout << "-";
    
}

int main(int argc, char ** argv) {
    
    int numOfDir = 0;
    unsigned long filesize = 0;
    struct stat mystat;
    DIR* d;
    struct dirent* dd;
    struct passwd* owner;
    
    for(int i = 1; i < argc; i+=1){
        
        if(!stat(argv[i],&mystat)){ // get info on the current directory given, if 0 -> succes, which is typecasted to false, -> "!"" "If succesful do stuff"
        
            
           
            mode_t mode = mystat.st_mode;
            owner = getpwuid(mystat.st_uid);
            
            premissions(mode); // print out premissions
            cout << argv[i] ; // print out path
            cout << " " << owner -> pw_name;
            

            if(S_ISDIR(mystat.st_mode)){ // is it a directory
                d = opendir(argv[1]);
                
                while((dd = readdir(d)) != NULL ){
                    numOfDir +=1;
                }
                cout << " " << numOfDir << endl;
            }
            else{ // not directory
                filesize = (unsigned long) mystat.st_size;
                cout << " " << filesize << endl;
            }
        }
        else{
            cout << argv[i] << " was not found" << endl;
        }
	numOfDir = 0;
    }    
    return 0;
}

