#include "Geometries.h"

Geometries::Geometries()
{
    //ctor
}

Geometries::~Geometries()
{
    //dtor
}

Line::Line()
{
    GeometryType = LINE;
}

Line::Line(glm::vec3 point , glm::vec3 direction)
{
    p=point;
    dir= glm::normalize(direction);
}

Line::~Line()
{

}

glm::vec3 Line::Point(glm::vec3 point)
{
    p = point;
    return p;
}

glm:: vec3 Line::Dir(glm::vec3 dire)
{
    dir = glm::normalize(dire);
    return dir;
}

glm::vec3 Line::Point()
{
    return p;
}

glm:: vec3 Line::Dir()
{
    return dir;
}




//Line





////Plane
Plane::Plane(){GeometryType = PLANE;}
Plane::Plane(glm::vec3 point , glm::vec3 direction)
{
    GeometryType = PLANE;
    p=point;
    dir= glm::normalize(direction);
}

Plane::~Plane(){}



glm::vec3 Plane::Point(glm::vec3 point)
{
    p = point;
    return p;
}

glm:: vec3 Plane::Dir(glm::vec3 dire)
{
    dir = glm::normalize(dire);
    return dir;
}

glm::vec3 Plane::Point()
{
    return p;
}

glm:: vec3 Plane::Dir()
{
    return dir;
}


//IntersectionFuntions

bool intersection(Plane *plane,Line *line,glm::vec3 *intersectionPoint )
{
    if(glm::dot(plane->Dir(),line->Dir())==0){return false;}

    float t = dot(     (-line->Point() + plane->Point()), plane->Dir()    )/dot(  line->Dir(), plane->Dir()    );
    *intersectionPoint = line->Point() + t*line->Dir();

}
