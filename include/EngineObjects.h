#ifndef ENGINEOBJECTS_H
#define ENGINEOBJECTS_H
#include"headers.h"


struct PSvec3
{
    float x; float y; float z ;
};








enum GameObjectType
{
    OBJECT,
    AMBIENTLIGHT,
    DIRECTIONALLIGHT,
    POINTLIGHT,
    CAMERA
};


class EngineObjects
{
    public:
        EngineObjects(std::string name="");
        ~EngineObjects();
            //Variables
        GameObjectType Type;
        Object RepresentngObject;
        virtual void setColor(float x,float y, float z);
        virtual void setIntense(float inten);
        virtual void setDirection(float x,float y,float z);
        virtual glm::vec3 getColor();
        virtual float getIntensity();
        virtual glm::vec3 getDirection();
    protected:

    private:



};

class EngineCamera: public EngineObjects
{
    public:
    EngineCamera(std::string name="");
    ~EngineCamera();
    Camera viewCamera;


};



class ambientLight: public EngineObjects
{
public:
    ambientLight();
    ~ambientLight();
    void setColor(float x,float y, float z);
    void setIntense(float inten);
private:

    glm::vec3 direction;
    glm::vec3 color ;
    float intensity;
};

class directionalLight :   public EngineObjects
{

public:
    directionalLight();
    ~directionalLight();
    void setColor(float x,float y, float z);
    void setIntense(float inten);
    void setDirection(float x,float y,float z);
     glm::vec3 getColor();
     float getIntensity();
     glm::vec3 getDirection();

private:

    glm::vec3 direction;
    glm::vec3 color ;
    unsigned int num;
    float intensity;

};

#endif // ENGINEOBJECTS_H
