#include"PSGameLibrary.h"

OpenGL3:: Object::Object()
{
    mat = &material;

}

OpenGL3::Object::~Object()
{
    //dtor
}

std::string OpenGL3::Object::getsourceFile()
{
    return sourceFile;
}
void OpenGL3::Object::LoadFromFile( const std::string &objectLocation)
{
    sourceFile = objectLocation;
    std::cout<<"importStarted"<<std::endl;
    glGenVertexArrays(1,&VaoID);//Generating VertexArray Object
    std::cout<<"Vertex array Generated"<<std::endl;
    glBindVertexArray(VaoID);
    std::cout<<"Vertex array Generated"<<std::endl;

    glGenBuffers(1,&PositionBufferID);//PositionBuffers
    glGenBuffers(1,&NormalBufferID);//NormalBuffers
    glGenBuffers(1,&TexCoordBufferID);//UV Buffers
    std::cout<<"BuffersGenerated"<<std::endl;
    obj.loadfromfile(objectLocation);//Load Model
    std::cout<<"ObjectLoaded"<<std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, PositionBufferID);//Working on position of vertices
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)* obj.positionData.size(),&obj.positionData[0],GL_STATIC_DRAW);//Presenting the Data
    glEnableVertexAttribArray(0);//Creating An attribute for position;
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);//Feeding The Data
    std::cout<<"Position Buffer Set"<<std::endl;

    glBindBuffer(GL_ARRAY_BUFFER,  NormalBufferID);//Working on normals of vertices
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)* obj.normalData.size(),&obj.normalData[0],GL_STATIC_DRAW);//Presenting the Data
    glEnableVertexAttribArray(1);//Creating An attribute for position;
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);//Feeding The Data
    std::cout<<"normal Buffer Set"<<std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, TexCoordBufferID);//Working on UV of vertices
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2)* obj.texCoordData.size(),&obj.texCoordData[0],GL_STATIC_DRAW);//Presenting the Data
    glEnableVertexAttribArray(2);//Creating An attribute for position;
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);//Feeding The Data
    std::cout<<"UV Buffer Set"<<std::endl;
    glBindVertexArray(0);//Unbind vertex Array object

}




void OpenGL3::Object::Render()
{
        mat->bindShader( &transforms);
        glBindVertexArray(VaoID);
        glDrawArrays(GL_TRIANGLES,0,obj.positionData.size());
        mat->unbindShader();
}
