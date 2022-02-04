#ifndef CAMERA_H
#define CAMERA_H
#include"common.h"
#include"Transform.h"

namespace OpenGL3{
class Camera
{
    public:
        Camera(float fov=45 , float aspect =4/3,float znear =0.01,float zfar=1000,const glm::vec3 cmaeraPosition = glm::vec3 (0,0,-1));
        virtual ~Camera();
        bool GenerateProjectionMat();
        glm::mat4 GenerateViewprojectionMat();
        glm::mat4 getViewProjectionMat(){return ViewProjectionMat;}
        glm::mat4 getProjectionMat(){return ProjectionMat;}
        void setPosition(glm::vec3 pos);
        std::string Name="";
        float getFov();
        float getZnear();
        float getZfar();
        float getAspect();
        glm::vec3 Forward();
        glm::vec3 Position();
    protected:

    private:
        Transform transforms;
        glm::mat4 ProjectionMat;
        glm::mat4 ViewProjectionMat;

        float znear,zfar,fov,aspect;

};
}


#endif // CAMERA_H
