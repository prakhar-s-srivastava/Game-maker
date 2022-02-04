#ifndef COLLIDERS_H
#define COLLIDERS_H
#include"common.h"
#include"colliderTranforms.h"
#include"Geometries.h"

class colliders
{
    public:
        colliders();
        virtual ~colliders();
        enum ColliderType
        {
            SPHERE,
            BOXAABB,
            BOX
        };

        ColliderType Type;
        colliderTranforms ColliderTransforms;
    protected:

    private:
};



class sphereCollider : public colliders                                 //sphere collider
{
public :
    sphereCollider();
    sphereCollider(float radius  , glm::vec3 center = glm::vec3 (0,0,0));
    ~sphereCollider();
    glm::vec3 center();
    float radius();
    glm::vec3 center( glm::vec3 cen);
    float radius(float rad);
private:
    glm::vec3 Center;
    float Radius;

};




class boxAABB: public colliders                                         //AABB  collider
{

public :
    boxAABB();
    boxAABB( glm::vec3 maxV, glm::vec3 minV);
    ~boxAABB();
       float maxX,maxY,maxZ,minX,minY,minZ;
private:




};


bool intersection(sphereCollider *sp,Line *l , glm::vec3 *i = new(glm::vec3));
bool intersection(boxAABB *b,Line *l , glm::vec3 *i = new(glm::vec3));
bool intersection(boxAABB *b,boxAABB *l , glm::vec3 *i = new(glm::vec3));
bool intersection(boxAABB *b,sphereCollider *sp , glm::vec3 *i = new(glm::vec3));

#endif // COLLIDERS_H
