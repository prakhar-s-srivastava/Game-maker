#ifndef GEOMETRIES_H
#define GEOMETRIES_H
#include"common.h"

class Geometries
{
    public:
        Geometries();
        virtual ~Geometries();

        enum geometryType
        {
            LINE,
            PLANE
        };

        geometryType GeometryType;
    protected:

    private:
};




class Line: public Geometries
{
public:
    Line();
    Line( glm::vec3 point , glm::vec3 direction );
    ~Line();

    glm::vec3 Point();
    glm:: vec3 Dir();
    glm::vec3 Point(glm::vec3 point);
    glm:: vec3 Dir(glm::vec3 dire);


    private:
    glm::vec3 p;
    glm::vec3 dir;
};




class Plane : public Geometries
{

public:
    Plane(glm::vec3 point , glm::vec3 direction);
    Plane();
    ~Plane();
     glm::vec3 Point();
    glm:: vec3 Dir();
    glm::vec3 Point(glm::vec3 point);
    glm:: vec3 Dir(glm::vec3 dire);

private:
    glm::vec3 p;
    glm::vec3 dir;

};

bool intersection(Plane *plane,Line *l,glm::vec3 *intersectionPoint = new(glm::vec3));

#endif // GEOMETRIES_H
