#ifndef GRAPHICSRENDERAPI_H_INCLUDED
#define GRAPHICSRENDERAPI_H_INCLUDED
#include<PSGameLibrary.h>
#ifdef OPENGL3
#define GLEW_STATIC
#include<Gl/glew.h>
#endif // OPENGL3
#include<string>
#include"GamePhysics.h"
#include"EngineObjects.h"
#include<GLFW/glfw3.h>

#ifdef OPENGL3
using namespace OpenGL3; // Setting namespace for opengl3+
#endif // OPENGL3


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
        GamePhysicsCollider *collider =NULL;
        virtual void setColor(float x,float y, float z);
        virtual void setIntense(float inten);
        virtual void setDirection(float x,float y,float z);
        virtual glm::vec3 getColor();
        virtual float getIntensity();
        virtual glm::vec3 getDirection();

        virtual void addCollider(colliders::ColliderType type = colliders::ColliderType::BOXAABB);
        virtual void addCollider(float radious , glm::vec3 center= glm::vec3(0,0,0));
        virtual void addCollider( glm::vec3 maxV  , glm::vec3 minV);
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


























extern EngineObjects* selectedObject;
extern EngineCamera* selectedCamera;
extern std::vector<EngineCamera*> CameraInScene;
extern std::vector<EngineObjects*> SceneObjects;
extern std::vector<Material*> MaterialList;
extern std::vector<Texture*> TextureList;
extern char MaterialName[100][50];
extern char TextureName[100][50];
extern void addObject(std::string name ="",std::string location = "");
extern void renderScene();
extern void setPosition(std::string name,float x,float y ,float z);
extern void setRotation(std::string name,float x,float y ,float z);
extern void setScale(std::string name,float x,float y ,float z);
extern void setPosition(EngineObjects *obj,float x,float y ,float z);
extern void setRotation(EngineObjects *obj,float x,float y ,float z);
extern void setScale(EngineObjects *obj,float x,float y ,float z);
extern void setForward(std::string name,float x,float y ,float z);
extern void setUp(std::string name,float x,float y ,float z);
extern  void addAmbient();
extern void addDirectionalLight();
//extern void setUpCamera()
extern EngineObjects* findObjectByName(std::string name);
extern void createCamera(float fov, float aspect,float znear,float zfar);
extern void makeCurrentCamera();

//Materials
extern Material* findMaterialtByName(std::string name);
extern Texture* findTextureByName(std::string name);
extern void loadShaderInMateral(std::string name,std::string shaderPath);
extern void setShader(Material * M,std::string shader, std::string shadersource);
extern void addMaterial(std::string name);
extern void assignMaterial(EngineObjects* obj, Material * mat);
extern void setMateriaColor(Material * mat,float x, float y, float z);
extern glm::vec3 getMaterialColor( Material * mat);
extern void addTexture(std::string name ,std::string location="");
extern void setTexture(Material* mat , Texture * tex);
extern void recalculateNameList();

//Lights

extern setAmbientLightColor( float r,float g,float b);
extern setAmbientLightIntensity( float intensity);


//Getters
extern PSvec3 getPosition(std::string name);
extern PSvec3 getRotation(std::string name);
extern PSvec3 getScale(std::string name);

extern PSvec3 getPosition(EngineObjects* name);
extern PSvec3 getRotation(EngineObjects* name);
extern PSvec3 getScale(EngineObjects* name);

extern Material* getMaterial(std::string  name);
extern Material* getMaterial(EngineObjects* name);
extern Texture* getTexture(Material*  name);
extern int getShader(EngineObjects* name);
extern int getShader(std::string  name);

//camera
extern void CameraRayCast ( GLFWwindow *window);





#endif // GRAPHICSRENDERAPI_H_INCLUDED
