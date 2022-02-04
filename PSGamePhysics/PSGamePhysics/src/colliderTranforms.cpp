#include "colliderTranforms.h"

colliderTranforms::colliderTranforms()
{
    Position = glm::vec3(0,0,0);
    Rotation = glm::vec3(0,0,0);
    Scale = glm::vec3(1,1,1);
}

colliderTranforms::~colliderTranforms()
{

}


glm::vec3 colliderTranforms::pos()
        {
            return Position;
        }
glm::vec3 colliderTranforms::rot()
        {

            return Rotation;
        }
glm::vec3 colliderTranforms::scale()
        {
            return Scale;
        }

glm::vec3 colliderTranforms::pos(float x, float y,float z)
        {
            Position = glm::vec3 (x,y,z);
            return Position;
        }
glm::vec3 colliderTranforms::rot(float x, float y,float z)
        {
            Rotation = glm::vec3 (x,y,z);
            return Rotation;
        }
glm::vec3 colliderTranforms::scale(float x, float y,float z)
        {
            Scale = glm::vec3 (x,y,z);
            return Scale;
        }


glm::vec3 colliderTranforms::pos(glm::vec3 a){ Position = a;  return Position;  }
glm::vec3 colliderTranforms::rot(glm::vec3 a){Rotation = a;    return Rotation; }
glm::vec3 colliderTranforms::scale(glm::vec3 a){ Scale = a;   return Scale; }
