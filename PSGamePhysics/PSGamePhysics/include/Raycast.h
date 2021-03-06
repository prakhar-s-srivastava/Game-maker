#ifndef RAYCAST_H
#define RAYCAST_H
#include"common.h"
#include"colliders.h"
#include "Geometries.h"
class Raycast
{
    public:
        Raycast(glm::vec3 origin , glm::vec3 direction, std::vector<colliders*> *colliderArray);
        Raycast(glm::vec3 origin , glm::vec3 direction, colliders*colliderArray);
        virtual ~Raycast();

        void* cast();


    protected:

    private:
        bool RayIntersection(Line ray, sphereCollider *collider) ;
        bool RayIntersection(Line ray, boxAABB *collider) ;
        Line Ray;
        std::vector<colliders*> *colliderArrays;

};

#endif // RAYCAST_H
