#include"PSGameLibrary.h"

OpenGL3::Transform::Transform()
{
   setPosition(glm::vec3(0.0,0.0,0.0));
   setRotation(glm::vec3(0.0,0.0,0.0));
   setScale(glm::vec3(1.0,1.0,1.0));
   setForward(glm::vec3(0,0,1));
   setUp(glm::vec3(0,1,0));

}

OpenGL3::Transform::~Transform()
{
    //dtor
}
bool OpenGL3::Transform::setPosition(float x,float y, float z){setPosition(glm::vec3(x,y,z)); return true;}
bool OpenGL3::Transform::setRotation(float x,float y, float z){setRotation(glm::vec3(x,y,z)); return true;}
bool OpenGL3::Transform::setScale(float x,float y, float z){setScale(glm::vec3(x,y,z)); return true;}

bool OpenGL3::Transform::setPosition(glm::vec3 pos)
    {
        Position=pos;
        TranslateMat = glm::translate(Position);
        GenerateModelTransformMat();
        return true;
    }
bool OpenGL3::Transform::setRotation(glm::vec3 rot)
    {
        Rotation=rot;
        QuaternionMat = glm::rotate(glm::radians(Rotation.x),glm::vec3(1,0,0)) * glm::rotate(glm::radians(Rotation.y),glm::vec3(0,1,0))
        *glm::rotate(glm::radians(Rotation.z),glm::vec3(0,0,1)) ;
        Forward=QuaternionMat*glm::vec4(Forward,1.0);
        Up = QuaternionMat*glm::vec4(Up,1.0);
        glm::normalize(Forward);
        glm::normalize(Up);
        GenerateModelTransformMat();
        return true;
    }
bool OpenGL3::Transform::setScale(glm::vec3 scal)
    {
        Scale=scal;
        ScaleMat = glm::scale(glm::vec3(Scale));
        GenerateModelTransformMat();
        return true;
    }
bool OpenGL3::Transform::setForward(glm::vec3 forw)
{
    Forward = forw;
    return true;
}

bool OpenGL3::Transform::setUp(glm::vec3 up)
{
    Up = up;
    return true;
}

void OpenGL3::Transform::GenerateModelTransformMat()
{

    ModelTransformMat = TranslateMat*QuaternionMat*ScaleMat;
}


