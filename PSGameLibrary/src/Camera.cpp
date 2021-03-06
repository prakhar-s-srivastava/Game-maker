#include  "PSGameLibrary.h"


// Generates a Camera Default
OpenGL3::Camera::Camera(float fov, float aspect,float znear ,float zfar,const glm::vec3 cmaeraPosition )
{
    //setting CameraVariables
    this->zfar=zfar;
    this->znear =znear;
    this->fov=fov;
    this->aspect=aspect;
    transforms.setPosition(cmaeraPosition);
    GenerateProjectionMat();
}

OpenGL3::Camera::~Camera()
{
    //dtor
}


bool OpenGL3::Camera::GenerateProjectionMat()
{
      ProjectionMat = glm::perspective(glm::radians(fov),aspect,znear,zfar);
      GenerateViewprojectionMat();
}

glm::mat4 OpenGL3::Camera::GenerateViewprojectionMat()
{
    Print(transforms.getPosition(),"Position");
    Print(transforms.getUp(),"Up");
   ViewProjectionMat = ProjectionMat*glm::lookAt(transforms.getPosition(),transforms.getPosition()+transforms.getForward(),transforms.getUp());
   return ViewProjectionMat;
}

void OpenGL3::Camera:: setPosition(glm::vec3 pos)
{
    transforms.setPosition(pos);
    GenerateViewprojectionMat();
}


float OpenGL3::Camera::getFov(){return fov;}
float OpenGL3::Camera::getZnear(){return znear;}
float OpenGL3::Camera::getZfar(){return zfar;}
float OpenGL3::Camera::getAspect(){return aspect;}

glm::vec3 OpenGL3::Camera::Forward()
{
    return transforms.getForward();
}

glm::vec3 OpenGL3::Camera::Position()
{
    return transforms.getPosition();
}
