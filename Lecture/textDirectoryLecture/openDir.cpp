#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>


using namespace std;



int main(int argc, char** argv){

	DIR* d = opendir(argv[1]);	// opens directory based on given named and stored in structure d 
	struct dirent* dd;

	while((dd = readdir(d)) != NULL ){ // while dircetory has not reached to end 
		
		struct stat s;
		string fname = argv[1] + string("/") + (dd->d_name); // path, "/" , name .. needs a c string for the + operation so use a string object to create it 
		stat(fname.c_str(), &s); // have to use c_string object to use these old c libaries

		cout << dd->d_name << " "  << endl;  // prints all directories in the given directory, // prints if its a directory, 1 yes 0 no
		
		if(S_ISDIR(s.st_mode)){		// only prints the first level in directoris													
			DIR* subd = opendir(fname.c_str());
			struct dirent* subdd;

			while((subdd = readdir(subd)) != NULL ){ 
		
				struct stat s;
				string fname = argv[1] + string("/") + (subdd->d_name); 
				stat(fname.c_str(), &s);
				cout << "	"<<subdd->d_name << " "  << endl;
			}
		}
	}
	return 0;
}
