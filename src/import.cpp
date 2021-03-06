#include "import.h"


bool import(const char * fileLocation)
{
    std::cout<<"file name "<<getFileName(fileLocation)<<std::endl;
    if( !strcmp(getExtension(fileLocation),".obj"))
    {
        addObject(std::string(getFileName(fileLocation)),std::string(fileLocation));
    }

    if( !strcmp(getExtension(fileLocation),".jpeg") ||  !strcmp(getExtension(fileLocation),".jpg")  ||  !strcmp(getExtension(fileLocation),".png") )
    {
        addTexture(std::string(getFileName(fileLocation)),std::string (fileLocation));
    }

    if( !strcmp(getExtension(fileLocation),".json"))
    {
        ImportScene(std::string(fileLocation));
    }

}
