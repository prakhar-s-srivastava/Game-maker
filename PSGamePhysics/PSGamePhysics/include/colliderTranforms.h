#ifndef COLLIDERTRANFORMS_H
#define COLLIDERTRANFORMS_H
#include<glm/glm.hpp>
//sphere collider

class colliderTranforms
{
    public:
        colliderTranforms();
        virtual ~colliderTranforms();
        glm::vec3 pos();
        glm::vec3 rot();
        glm::vec3 scale();

        glm::vec3 pos(float x, float y,float z);
        glm::vec3 rot(float x, float y,float z);
        glm::vec3 scale(float x, float y,float z);

        glm::vec3 pos(glm::vec3 a);
        glm::vec3 rot(glm::vec3 a);
        glm::vec3 scale(glm::vec3 a);

    protected:

    private:
        glm::vec3 Position, Rotation ,Scale;


};

#endif // COLLIDERTRANFORMS_H
