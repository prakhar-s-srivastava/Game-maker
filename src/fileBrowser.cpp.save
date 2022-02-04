#include "fileBrowser.h"

std::vector<std::string> pathlist;
std::vector<std::string> files;
 std::vector<std::string> directories;
 std::vector<std::string> filesDisplay;
 std::vector<std::string> directoriesDisplay;
 unsigned int length =10;

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}


void browseFiles(const char *path){
    files.clear();
    directories.clear();
struct dirent *entry;
   DIR *dir = opendir(path);

   if (dir == NULL) {
        std::cout << "not a dir"<<std::endl;
      return;
   }
   while ((entry = readdir(dir)) != NULL) {
   std::string actualpath = listToString() + std::string(entry->d_name);
   if(  !strcmp("..",entry->d_name) || !strcmp(".",entry->d_name) ) continue;
   if(is_regular_file(actualpath.c_str()) )
   {

    files.push_back( std::string(entry->d_name));
   }
   else{
        directories.push_back(std::string(entry->d_name));
   }

}
closedir(dir);
}
std::string listToString()
{
    std::string returnString="";
    std::vector<std::string>::iterator itr;
    for(itr= pathlist.begin();itr!= pathlist.end();itr++)
    {
        returnString+=(*itr);
    }

    return returnString;
}

const char *getExtension(const char* filname)
{
    unsigned int it=0;
     unsigned int itt=0;
    static char  extention[50] ;

    while(filname[it] != '\0')
    {

        extention[itt]=filname[it];
         it++;
        itt++;
          if(filname[it] == '.')
        {
            itt=0;
        }
    }

    while (itt<49)
    {
        extention[itt] ='\0';
         itt++;
    }

    return extention;
}

const char* getFileName(const char* filname)
{
    unsigned int it=0;
     unsigned int itt=0;
    static char  extention[50] ;

    while(filname[it] != '\0')
    {

        extention[itt]=filname[it];

        itt++;
          if(filname[it] == '/')
        {
            itt=0;
        }
         it++;
    }

    while (itt<49)
    {
        extention[itt] ='\0';
         itt++;
    }

    return extention;
}


void copyFIle(std::string sourceFilePath,std::string destinationFolder,std::string  destinationFileName)
{
    FILE* source = fopen(sourceFilePath.c_str(),"r");
    FILE* destination =fopen(std::string(destinationFolder+ "/"+destinationFileName).c_str(),"w");
    char line[512];
    if(source ==NULL || destination ==NULL)
    {
        printf("accessDenied");
        return;
    }


    while(!feof(source))
    {
        fgets(line,512,source);
        if(feof(source))break;
        fputs(line,destination);
    }
    fclose(source);
    fclose(destination);
}



void copyFIleBinary(std::string sourceFilePath,std::string destinationFolder,std::string  destinationFileName)
{
    FILE* source = fopen(sourceFilePath.c_str(),"rb");
    FILE* destination =fopen(std::string(destinationFolder+ "/"+destinationFileName).c_str(),"wb");
    char line[4096];
    if(source ==NULL || destination ==NULL)
    {
        printf("accessDenied");
        return;
    }


    while(!feof(source))
    {
        fread(line,4096,1,source);
        if(feof(source))break;
        fwrite(line,4096,1,destination);
    }
    fclose(source);
    fclose(destination);

}
