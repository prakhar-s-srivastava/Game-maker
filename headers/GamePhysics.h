#ifndef GAMEPHYSICS_H
#define GAMEPHYSICS_H
#include<PSGamePhysics.h>

class GamePhysicsCollider
{
    public:
        GamePhysicsCollider( colliders::ColliderType type = colliders::ColliderType::BOXAABB);
        GamePhysicsCollider( float radious , glm::vec3 center= glm::vec3(0,0,0));
        GamePhysicsCollider( glm::vec3 maxV  , glm::vec3 minV);

        virtual ~GamePhysicsCollider();
         colliders *collider;
    protected:

    private:

};





#endif // GAMEPHYSICS_H
