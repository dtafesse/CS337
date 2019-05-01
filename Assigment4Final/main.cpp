#include "main.h"

using namespace std;

string getRelativePath(string line){
    size_t firstComma = line.find_first_of(",");
    size_t lastSlash = line.find_last_of("/");
    size_t secondComma = line.find(",", firstComma+1);
    string path = line.substr(1, lastSlash-1);
    string size = line.substr(firstComma+1,(secondComma-firstComma-1));
    string nameOfFile = line.substr(lastSlash+1, firstComma-lastSlash-1);
    string relativePath = path.substr(path.find_last_of("/"),path.size());
    
    return relativePath;
}
string getActualPath(string line){
    size_t lastSlash = line.find_last_of("/");
    string path = line.substr(1, lastSlash-1);
    
    return path;
}
string getNameOfFIle(string line){
    size_t firstComma = line.find_first_of(",");
    size_t lastSlash = line.find_last_of("/");
    
    return line.substr(lastSlash+1, firstComma-lastSlash-1);
}
string getActualPathWithNameOfFile(string line){
    size_t firstComma = line.find_first_of(",");
    string path = line.substr(1, firstComma-1);
    
    return path;
}
string getSize(string line){
    size_t firstComma = line.find_first_of(",");
    size_t secondComma = line.find(",", firstComma+1);
    
    return line.substr(firstComma+1,(secondComma-firstComma-1));
}
void makeDirectoriesTree(string path){
    string key = "/";
    vector<size_t> positions; // holds all the positions that "/" occurs within path
    size_t pos = path.find(key, 0);
    while(pos != string::npos)
    {
        positions.push_back(pos);
        pos = path.find(key,pos+1);
    }
    vector<string> directories;
    string lin = "";
    for(int i = 0; i < positions.size(); i+=1){
        if((positions.size() - i) == 1){
            break;
        }
        lin = path.substr(0, positions[i+1]);
        directories.push_back(lin);
        
        int j = mkdir(lin.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if(j==-1)//creating a directory
        {
            if( errno != EEXIST){
                cerr<<"Error1 :  "<< strerror(errno) <<endl;
                return;
            }
        }
    }
    lin = path.substr(0);
    int j = mkdir(lin.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(j==-1)//creating a directory
    {
        if( errno != EEXIST){
            cerr<<"Error1 :  "<< strerror(errno) <<endl;
            return;
        }
    }
}
void readBuffer(ssize_t sizeOfBuffer, string path, string nameOfFile, string pathWithFileName){
    makeDirectoriesTree(path);
    
    ifstream read;//reading a file
    ofstream write;
    
    string line;
    read.open(pathWithFileName.c_str(),ios_base::in);
    write.open((path+"/"+nameOfFile).c_str(), ios_base::app);
    
    if (read.is_open()){
        while (!read.eof() ){
            getline (read,line);
            write << line << endl;
        }
        read.close();
        write.close();
    }
    else
        cout << "Unable to open or write file";
}
void openArchive(const char *ArchiveTextFile, const char *ParentPathTarget){
    string line;
    string size, relativePath, nameOfFile, offset, path, ActualpathWithName;
    ssize_t sizeOfBuffer = 0;
    
    ifstream read;//reading a file
    ofstream write;
    
    read.open(ArchiveTextFile,ios_base::in);
    
    if (read.is_open()){
        while (!read.eof() ){
            getline (read,line);
            size = getSize(line);
            sizeOfBuffer = atoi(size.c_str());
            nameOfFile = getNameOfFIle(line);
            
            path = ParentPathTarget + getActualPath(line);
    
            ActualpathWithName = getActualPathWithNameOfFile(line);
    
            readBuffer(sizeOfBuffer, path, nameOfFile, ActualpathWithName);
        }
        read.close();
        write.close();
    }
    else
        cout << "Unable to open or write file";
}
void writeToText(const char *path, string lineToWriteToArchive, const char *ArchiveTextFile){
    
    string line;
    ofstream write;
    
    write.open(ArchiveTextFile, ios_base::app);
    
    if (write.is_open()){
        string entry = "<" + lineToWriteToArchive + ">";
        write << entry << endl;
        write.close();
    }
    else
        cout << "Unable to open or write file";
}
void ArchiveDirectoy(const char *source, const char *ArchiveTextFile)
{
    DIR *dir;
    struct dirent *entry;
    struct stat mystat;
    
    if (!(dir = opendir(source)))
        return;
    if (!(entry = readdir(dir)))
        return;
    
    unsigned int filesize = 0;
    
    do {
        char path[1024];
        int len = snprintf(path, sizeof(path)-1, "%s/%s", source, entry->d_name);
        path[len] = 0;
        
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                continue;
            }
            ArchiveDirectoy(path, ArchiveTextFile);
        }
        else{
            string PathString = path;
            stat(path, &mystat);
            filesize = (unsigned int) mystat.st_size;
            
            string intString;
            stringstream out;
            out << filesize;
            intString = out.str();
            /// Set up the String to be printed in Text File
            string line = PathString;
            line = line + ","+ intString;
            
            writeToText(path, line.c_str(), ArchiveTextFile);
        }
    } while ((entry = readdir(dir)));
    closedir(dir);
}
int main(int argc, char** argv)
{
    if(strcmp (argv[1],"-c") == 0){
        string argu = argv[3];
        string ArchiveTextFile = argu+"/Archive.txt";
        ArchiveDirectoy(argv[2], ArchiveTextFile.c_str());
    }else{
        if(strcmp (argv[1],"-e") == 0){
            openArchive(argv[2], argv[3]);
        }
    }
    return 0;
}
