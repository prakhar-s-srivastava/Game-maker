#include <iostream>
#include<PSGamePhysics.h>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    std::vector<colliders*>  testVector;
        sphereCollider col;
        testVector.push_back(new sphereCollider(2,glm::vec3 (50,0,0)));
        Raycast selecteRay(glm::vec3(0,0,0), glm::vec3(0,0,1),&testVector);


        //AABB Line
        boxAABB box;
        box.minX=-1;
        box.maxX=1;
         box.minY=-1;
        box.maxY=1;
         box.minZ=-1;
        box.maxZ=1;

        box.ColliderTransforms.pos(0,-0.99,1);

        Line line(glm::vec3 (0,0,0),glm::vec3(0,0,1));
        if(intersection(&box,&line))
        {
              cout << " AABB box collision with Line!" << endl;
        }
        else{
            cout << " no AABB box collision with Line!" << endl;
        }



        //AABB RAY
        testVector.push_back(new boxAABB);
        colliders* coliderPointer =(colliders*)selecteRay.cast();
        std::cout <<  " collider Type " <<coliderPointer->Type<<std::endl;


        //AABB intersection test;
        boxAABB testBoxAABB1,testBoxAABB2;
        testBoxAABB1.ColliderTransforms.pos(2,0,-1.9);
        if(intersection(&testBoxAABB1,&testBoxAABB2))
        {
            cout<<"AABB collision test"<<endl;

        }
        else{
            cout<<"AABB collision test failed"<<endl;

        }

        //AABB  sphere
        col.radius(0.9);
        if(intersection(&testBoxAABB1,&col))
        {
            cout<<"AABB  sphere collision test"<<endl;

        }
        else{
             cout<<"AABB  sphere collision test fail"<<endl;
        }


    Line line1(glm::vec3(0,0,0),glm::vec3(1,0,0));
    Plane plane1(glm::vec3(-6,0,0),glm::vec3(1,-0.3,0));

    glm::vec3 ints;

    intersection(&plane1,&line1,&ints);
    std::cout<<"intersection "<< ints.x<<"  "<<ints.y<<" "<<ints.z<<std::endl;

    return 0;
}
