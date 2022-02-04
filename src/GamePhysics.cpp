#include "GamePhysics.h"

GamePhysicsCollider::GamePhysicsCollider(colliders::ColliderType type)
{
    if(type == colliders::ColliderType::BOXAABB)
    {
        collider = new boxAABB(glm::vec3(1,1,1),glm::vec3(-1,-1,-1));
        
    }
    else if( type == colliders::ColliderType::SPHERE)
    {
        collider = new sphereCollider;

    }
}

GamePhysicsCollider::GamePhysicsCollider( float radious , glm::vec3 center)
{
    collider = new sphereCollider(radious,center);


}


GamePhysicsCollider::GamePhysicsCollider( glm::vec3 maxV , glm::vec3 minV)
{
    collider = new boxAABB(maxV,minV);
}


GamePhysicsCollider::~GamePhysicsCollider  ()
{
    //dtor
}

