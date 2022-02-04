#ifndef OBJECT_H
#define OBJECT_H
#include"common.h"
#include"Material.h"
#include"Transform.h"


namespace OpenGL3{





class Object
{
    public:
        Object();
        virtual ~Object();
        //Variables
            Material *mat;
            Transform transforms;
            std::string Name="";

        //Methods
        void Render();
        void LoadFromFile( const std::string &objectLocation);
        std::string getsourceFile();

    protected:

    private:
         std::string sourceFile;
         ObjectImport obj;
         GLuint VaoID,PositionBufferID,NormalBufferID,TexCoordBufferID;


};


}

#endif // OBJECT_H
