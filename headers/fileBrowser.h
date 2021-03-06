#ifndef FILEBROWSER_H
#define FILEBROWSER_H
#include"headers.h"


extern std::vector<std::string> pathlist;
extern std::vector<std::string> files;
extern std::vector<std::string> directories;
extern std::vector<std::string> filesDisplay;
extern std::vector<std::string> directoriesDisplay;
void browseFiles(const char *path);
int is_regular_file(const char *path);
extern unsigned int length;
std::string listToString();
const char* getExtension(const char* filname);
const char* getFileName(const char* filname);
void copyFIle(std::string sourceFilePath,std::string destinationFolder,std::string  destinationFileName);
void copyFIleBinary(std::string sourceFilePath,std::string destinationFolder,std::string  destinationFileName);

#endif // FILEBROWSER_H
