#ifndef TRANSFORM_H
#define TRANSFORM_H
#include"common.h"

namespace OpenGL3{
class Transform
{
    public:
        Transform();
        virtual ~Transform();

        glm::vec3 getPosition(){return Position;}
        glm::vec3  getRotation(){return Rotation;}
        glm::vec3  getScale(){return Scale;}
        glm::vec3 getForward(){return Forward;}
        glm::vec3 getUp(){return Up;}

        bool setPosition(glm::vec3 pos);
        bool setRotation(glm::vec3 rot);
        bool setScale(glm::vec3 scal);
        bool setForward(glm::vec3 forw);
        bool setUp(glm:: vec3 up);
        bool setPosition(float x,float y, float z);
        bool setRotation(float x,float y, float z);
        bool setScale(float x,float y, float z);
        void GenerateModelTransformMat();
        glm::mat4 getModelTransformMat(){return ModelTransformMat;}
        glm::mat4 TranslateMat;
        glm::mat4 QuaternionMat;
        glm::mat4 ScaleMat;

    protected:

    private:
        glm::vec3 Position,Rotation,Scale,Forward,Up;
        glm::mat4 ModelTransformMat;
};
}
#endif // TRANSFORM_H
