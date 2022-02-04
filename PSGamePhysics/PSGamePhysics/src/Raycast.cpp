#include "PSGamePhysics.h"

Raycast::~Raycast()
{
    //dtor
}


bool Raycast::RayIntersection(Line ray, sphereCollider *collider)
{
    return intersection(collider,&ray);

}

bool Raycast::RayIntersection(Line ray, boxAABB *collider)
{
    return intersection(collider,&ray);

}



Raycast::Raycast(glm::vec3 origin, glm::vec3 direction, std::vector<colliders*> *colliderArray)
{
    //sorting algo
    Ray.Point(origin);
    Ray.Dir( glm::normalize(direction));
    colliderArrays = colliderArray;
}


Raycast::Raycast(glm::vec3 origin , glm::vec3 direction, colliders*colliderArray)
{


}


void* Raycast::cast()
{
    std::vector<colliders*>::iterator itr;
    void *collider =NULL;
    colliders *temp = NULL;
    for(itr = (*colliderArrays).begin();itr != (*colliderArrays).end();itr++)
    {
        if( (*itr)->Type == colliders::SPHERE  )
        {
                sphereCollider *spc= (sphereCollider*) (*itr);
                if(RayIntersection(Ray,spc))
                {
                    std::cout <<"intersection SPHERE"<<std::endl;
                     temp = spc;
                }
        }



         if( (*itr)->Type == colliders::BOXAABB  )
        {
                boxAABB *spc= (boxAABB*) (*itr);
                if(RayIntersection(Ray,spc))
                {
                    std::cout <<"intersection boxAABB"<<std::endl;
                    temp = spc;
                }
        }

            if(collider == NULL) {collider = temp;}
            if(collider != NULL){
            colliders * temp1 = (colliders*) collider;
            if( glm::length2(Ray.Point()-temp->ColliderTransforms.pos())   < glm::length2(Ray.Point()-temp1->ColliderTransforms.pos())  )
            {
                collider = temp;
                std::cout <<"intersection type"<<temp->Type<<std::endl;
            }
            }

    }

    if(collider ==NULL)
    {
        std::cout <<" no intersection"<<std::endl;
        return NULL;
    }

    return collider;

}
