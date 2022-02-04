#include "colliders.h"

colliders::colliders()
{

}

colliders::~colliders()
{

}



/////Sphere/////

sphereCollider::sphereCollider()
{
    Type = SPHERE;
    Radius = 1;
    Center = glm::vec3 (0,0,0);

}

sphereCollider::sphereCollider(float radius  , glm::vec3 center)
{
    Type = SPHERE;
    Radius = radius;
    Center = center;
}

 sphereCollider:: ~sphereCollider()
 {

 }

 glm::vec3 sphereCollider::center()
 {
     return Center;
 }

 float sphereCollider::radius()
 {
     return Radius;
 }

 glm::vec3 sphereCollider::center(glm::vec3 cen)
 {
     Center = cen;
     return Center;
 }

 float sphereCollider::radius( float rad)
 {
     Radius = rad;
     return Radius;
 }




////boxAABB/////

boxAABB::boxAABB()
{
    Type = BOXAABB;
        minX=-1;
        maxX=1;
         minY=-1;
        maxY=1;
         minZ=-1;
        maxZ=1;
}

boxAABB::boxAABB( glm::vec3 maxV, glm::vec3 minV)
{
     Type = BOXAABB;
        minX=minV.x;
        maxX=maxV.x;
         minY=minV.y;
        maxY=maxV.y;
         minZ=minV.z;
        maxZ=maxV.z;

}

boxAABB::~boxAABB()
{

}


//intersections;

bool intersection(sphereCollider *sp,Line *l , glm::vec3 *i )
{
     glm::vec3 cross = glm::cross(l->Dir(),sp->ColliderTransforms.pos()+ sp->center() - l->Point());
    float distance = glm::length2(cross);
    if(distance<= sp->radius()) {return true;

    }
    return false;
}


/////////////////////
bool intersection(boxAABB *b,Line *l , glm::vec3 *i)
{
        std::cout<<"line start"<<std::endl;
    Plane plane( glm::vec3(b->maxX,0,0),glm::vec3 (1,0,0));
    glm::vec3 g;
    Line line = *l;
    line.Point(line.Point() - b->ColliderTransforms.pos());
    std::cout<<"line position"<<line.Point().x<< "  "<< line.Point().y<< "  "<<line.Point().z<<std::endl;
     std::cout<<"line direction"<<line.Dir().x<< "  "<< line.Dir().y<< "  "<<line.Dir().z<<std::endl;
    for(int it =0;it<2;it++){

    if(intersection(&plane,&line,&g))
    {
        if(g.y > b->minY &&  g.y <b->maxY   && g.z > b->minZ&&  g.z <b->maxZ   ) {
                                std::cout<<"line intersection x"<<g.x<< "  "<<g.y<< "  "<<g.z<<std::endl;
                                return true;
}
        else {  plane.Point(glm::vec3(b->minX,0,0));}
    }

    }


   //y
    plane.Point(glm::vec3(0,b->maxY,0));
    plane.Dir(glm::vec3 (0,1,0));
   for(int it =0;it<2;it++){

    if(intersection(&plane,&line,&g))
    {
        if(g.x > b->minX &&  g.x <b->maxX  && g.z > b->minZ&&  g.z <b->maxZ   ) {
                std::cout<<"line intersection y"<<g.x<< "  "<<g.y<< "  "<<g.z<<std::endl;
                return true;
}
        else {  plane.Point(glm::vec3(0,b->minY,0));}
    }

    }



    //z

    plane.Point(glm::vec3(0,0,b->maxZ));
    plane.Dir(glm::vec3 (0,0,1));
   for(int it =0;it<2;it++){

    if(intersection(&plane,&line,&g))
    {
        if(g.y > b->minY &&  g.y <b->maxY   &&  g.x > b->minX&&  g.x < b->maxX   ) {
                 std::cout<<"line max z"<<b->maxZ<<"  "<<b->minZ<<std::endl;
                std::cout<<"line intersection z"<<g.x<< "  "<<g.y<< "  "<<g.z<<std::endl;
            std::cout<<g.z<<std::endl;
return true;}
        else {  plane.Point(glm::vec3(0,0,b->minZ));}
    }

    }

    return false;

}




bool intersection(boxAABB *b,boxAABB *l , glm::vec3 *i )
{
    bool x,y,z=false;
    if((b->maxX+b->ColliderTransforms.pos().x) >(l->minX+l->ColliderTransforms.pos().x)
         &&  (b->minX+b->ColliderTransforms.pos().x) < (l->maxX+l->ColliderTransforms.pos().x)){ x=true;}
            else{ return false;}

    if((b->maxY  +b->ColliderTransforms.pos().y) >(l->minY+l->ColliderTransforms.pos().y)
         &&  (b->minY+b->ColliderTransforms.pos().y) <(l->maxY+l->ColliderTransforms.pos().y)){ y=true;}
         else{return false;}

    if((b->maxZ  +b->ColliderTransforms.pos().z )>(l->minZ+l->ColliderTransforms.pos().z)
         &&  (b->minZ+b->ColliderTransforms.pos().z) < (l->maxZ+l->ColliderTransforms.pos().z)){ z=true;}
         else{return false;}

         return true;

}



bool intersection(boxAABB *b,sphereCollider *sp , glm::vec3 *i )
{
    glm::vec3 vertices[8] = {
    glm::vec3(b->ColliderTransforms.pos().x+b->minX,b->ColliderTransforms.pos().y+b->minY,b->ColliderTransforms.pos().z+b->minZ),
    glm::vec3(b->ColliderTransforms.pos().x+b->maxX,b->ColliderTransforms.pos().y+b->minY,b->ColliderTransforms.pos().z+b->minZ),
    glm::vec3(b->ColliderTransforms.pos().x+b->minX,b->ColliderTransforms.pos().y+b->maxY,b->ColliderTransforms.pos().z+b->minZ),
    glm::vec3(b->ColliderTransforms.pos().x+b->minX,b->ColliderTransforms.pos().y+b->minY,b->ColliderTransforms.pos().z+b->maxZ),
    glm::vec3(b->ColliderTransforms.pos().x+b->maxX,b->ColliderTransforms.pos().y+b->maxY,b->ColliderTransforms.pos().z+b->minZ),
    glm::vec3(b->ColliderTransforms.pos().x+b->maxX,b->ColliderTransforms.pos().y+b->minY,b->ColliderTransforms.pos().z+b->maxZ),
    glm::vec3(b->ColliderTransforms.pos().x+b->minX,b->ColliderTransforms.pos().y+b->maxY,b->ColliderTransforms.pos().z+b->maxZ),
    glm::vec3(b->ColliderTransforms.pos().x+b->maxX,b->ColliderTransforms.pos().y+b->maxY,b->ColliderTransforms.pos().z+b->maxZ)
};

    glm::vec3 normals[3] = {
    glm::vec3 (1,0,0),
    glm::vec3(0,1,0),
    glm::vec3(0,0,1)
    };

    for(int it=0;it <3;it++)
    {
        bool intersect =false;
        float center = glm::dot(normals[it], sp->ColliderTransforms.pos()+sp->center());
         float maxD,minD;
         maxD = minD = glm::dot(normals[it],vertices[0]);
        for(int itt =0;itt<8;itt++)
        {
            float vertex = glm::dot(normals[it],vertices[itt]);
            maxD = vertex>maxD ? vertex : maxD;
            minD = vertex<minD ? vertex : minD;
            if(abs(center-vertex) < sp->radius())
            {
                intersect =true;
                break;
            }

        }

        if(center>minD && center<maxD)
        {

            intersect =true;
        }

        if(!intersect){return false;}

    }

        return true;


}
