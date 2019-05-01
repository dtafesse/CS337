#ifndef main_h
#define main_h

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sstream>
#include <cstddef>
#include <fcntl.h>
#include <ctype.h>
#include <vector>
#include <string>

using namespace std;

string getRelativePath(string line);
string getActualPath(string line);
string getNameOfFIle(string line);
string getSize(string line);
void makeDirectoriesTree(string path);
void readBuffer(ssize_t sizeOfBuffer, const char *ArchiveTextFile, string path,
                string nameOfFile);
void readBuffer(ssize_t sizeOfBuffer, const char *ArchiveTextFile, string path,
                string nameOfFile);
void writeToText(const char *path, string lineToWriteToArchive, const char *ArchiveTextFile);
void ArchiveDirectoy(const char *source, const char *ArchiveTextFile);


#endif /* mainV2_h */

