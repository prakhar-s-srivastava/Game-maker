    #ifndef PSGAMELIBRARY_H_INCLUDED
#define PSGAMELIBRARY_H_INCLUDED
#include"common.h"
#include"ObjectImport.h"
#include"Object.h"
#include"Lighting.h"
#include"Material.h"
#include"Camera.h"
#include"Transform.h"



extern OpenGL3::Camera *currentCamera;
extern OpenGL3::Material material;
extern AmbientLight ambient;
extern std::vector<DirectionalLight> directionalLights;

static void initilize ()
{
     glewExperimental = GL_TRUE;
     GLenum err=glewInit();
    if(GLEW_OK ==err)
    {

        std::cout<<"Glew initilized"<<std::endl;
    }
    else{
        std::cout<<"Glew NOT Initilized"<<std::endl;
    }

    currentCamera->setPosition(glm::vec3 (0,0,1));

    glClearColor(0.0,0.0,1.0,1.0);
    glEnable(GL_DEPTH);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    ambient.intensity =0;                                               //setting ambient light
    ambient.rgb =glm::vec3(0,0,0);


}

#endif // PSGAMELIBRARY_H_INCLUDED
