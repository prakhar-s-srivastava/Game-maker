#include"GraphicsRenderApi.h"
#include"EngineObjects.h"
#ifdef OPENGL3








EngineObjects::EngineObjects(std::string name)
{
    Type = OBJECT;

}

EngineObjects::~EngineObjects()
{

}

void EngineObjects::setColor(float x,float y, float z)
{

}

void EngineObjects::setIntense(float inten)
{

}
void EngineObjects::setDirection(float x,float y,float z)
{

}


 glm::vec3 EngineObjects::getColor(){}
float EngineObjects::getIntensity(){}
 glm::vec3 EngineObjects::getDirection(){}

 void EngineObjects::addCollider(colliders::ColliderType type)
 {
     collider = new GamePhysicsCollider(type);
     collider->collider->ColliderTransforms.pos(EngineObjects::RepresentngObject.transforms.getPosition());
 }
 void EngineObjects::addCollider(float radious , glm::vec3 center)
 {
        collider = new GamePhysicsCollider(radious,center);
        collider->collider->ColliderTransforms.pos(EngineObjects::RepresentngObject.transforms.getPosition());
 }
 void EngineObjects::addCollider( glm::vec3 maxV  , glm::vec3 minV)
 {
        collider = new GamePhysicsCollider(maxV,minV);
        collider->collider->ColliderTransforms.pos(EngineObjects::RepresentngObject.transforms.getPosition());

 }




 //engine camera

EngineCamera::EngineCamera(std::string name)
{

}

EngineCamera::~EngineCamera()
{

}


ambientLight::ambientLight(){ Type =AMBIENTLIGHT;}
ambientLight::~ambientLight(){}
void ambientLight::setColor(float x,float y, float z)
{
    ambient.rgb = glm::vec3(x,y,z);
}
void ambientLight::setIntense(float inten)
{
    ambient.intensity = inten;
}





directionalLight::directionalLight()
{
    DirectionalLight *light;
    DirectionalLight dir;
    directionalLights.push_back( dir);
    light=&directionalLights.back();
    num= directionalLights.size()-1;
    light->direction = glm::vec3(0,-1,0);
    light->color = glm::vec3(0.33,0.5,0.3);
    light->intensity=0.6;
    Type =DIRECTIONALLIGHT;
}

directionalLight::~directionalLight()
{

}

void directionalLight::setColor(float x,float y, float z)
{
    directionalLights[num].color = glm::vec3(x,y,z);
}

void directionalLight::setIntense(float inten)
{
    directionalLights[num].intensity =inten;
}

void directionalLight::setDirection(float x,float y,float z)
{
   directionalLights[num].direction = glm::vec3(x,y,z);
}

glm::vec3 directionalLight::getColor(){return directionalLights[num].color;}
float directionalLight::getIntensity(){return directionalLights[num].intensity;}
glm::vec3 directionalLight::getDirection(){return directionalLights[num].direction;}














 EngineObjects* selectedObject;
 EngineCamera* selectedCamera;
 std::vector<EngineCamera*> CameraInScene;
 std::vector<EngineObjects*> SceneObjects;
 std::vector<Material*> MaterialList;
 std::vector<Texture*> TextureList;
 char MaterialName[100][50] = {'\0'};
 char TextureName[100][50] = {'\0'};

void addObject(std::string name,std::string location)
{
    if(findObjectByName(name)!=NULL)
    {
        std::cout<<"found1"<<std::endl;
        name = name + ".copy";
        addObject(name,location);
        return;

    }
    SceneObjects.push_back(new EngineObjects);
    std::cout<<"size "<<SceneObjects.size()<<std::endl;
    if(!location.empty())
    {
        SceneObjects.back()->RepresentngObject.LoadFromFile(location);
    }
    SceneObjects.back()->RepresentngObject.mat->BuildShader();
    SceneObjects.back()->RepresentngObject.Name=name;
    SceneObjects.back()->addCollider();
    return;

}

void renderScene()
{
    std::vector<EngineObjects*>::iterator itr;
    //if(SceneObjects.size()>1)std::cout<<SceneObjects.size()<<std::endl;
    for(itr = SceneObjects.begin();itr!=SceneObjects.end();itr++)
    {
         (*itr)->RepresentngObject.Render();
    }
}

 EngineObjects* findObjectByName(std::string name)
{
    std::vector<EngineObjects*>::iterator itr;
    for(itr = SceneObjects.begin();itr!=SceneObjects.end();itr++)
    {
        if((*itr)->RepresentngObject.Name == name) return (EngineObjects*)(*itr);

    }

    return NULL;
}

 void setPosition(std::string name,float x,float y ,float z)
{
    findObjectByName(name)->RepresentngObject.transforms.setPosition(x,y,z);
    if( findObjectByName(name)->collider != NULL){
             printf("can  \n ");
    findObjectByName(name)->collider->collider->ColliderTransforms.pos(findObjectByName(name)->RepresentngObject.transforms.getPosition());
    }
    else{
        printf("cant get \n");
    }
}

 void setRotation(std::string name,float x,float y ,float z)
{
    findObjectByName(name)->RepresentngObject.transforms.setRotation(x,y,z);
}
 void setScale(std::string name,float x,float y ,float z)
{
    findObjectByName(name)->RepresentngObject.transforms.setScale(x,y,z);
}



 void setPosition(EngineObjects *obj,float x,float y ,float z)
 {
    obj->RepresentngObject.transforms.setPosition(x,y,z);
    if(obj->collider != NULL){
    obj->collider->collider->ColliderTransforms.pos(obj->RepresentngObject.transforms.getPosition());
    }

}
 void setRotation(EngineObjects *obj,float x,float y ,float z)
 {

    obj->RepresentngObject.transforms.setRotation(x,y,z);

 }
 void setScale(EngineObjects *obj,float x,float y ,float z)
 {
    obj->RepresentngObject.transforms.setScale(x,y,z);
}


 void setForward(std::string name,float x,float y ,float z)
{
    findObjectByName(name)->RepresentngObject.transforms.setForward(glm::vec3(x,y,z));
}
 void setUp(std::string name,float x,float y ,float z)
{
    findObjectByName(name)->RepresentngObject.transforms.setUp(glm::vec3(x,y,z));
}


void createCamera(float fov, float aspect,float znear,float zfar)
{
        CameraInScene.push_back(new EngineCamera);
        CameraInScene.back()->viewCamera = Camera(fov,aspect,znear,zfar);

}

void makeCurrentCamera()
{
    currentCamera  = &selectedCamera->viewCamera;
}

 void addAmbient()
 {
        ambient.intensity=1;
        ambient.rgb = glm::vec3(0.3,0.3,0.6);
        SceneObjects.push_back(new ambientLight);
        SceneObjects.back()->RepresentngObject.LoadFromFile("Resources/light-represent.obj");  //("AmbientLight","Resources/light-represent.obj");
        SceneObjects.back()->RepresentngObject.Name = "AmbientLight:Light";
        SceneObjects.back()->Type =AMBIENTLIGHT;
 }


 void addDirectionalLight()
 {
     SceneObjects.push_back(new directionalLight);
     SceneObjects.back()->RepresentngObject.LoadFromFile("Resources/light-represent.obj");
     SceneObjects.back()->RepresentngObject.Name = "directionalLight:Light" + std::to_string(directionalLights.size());
     SceneObjects.back()->Type =DIRECTIONALLIGHT;
 }

//Material

Material* findMaterialtByName(std::string name)
{

    std::vector<Material*>::iterator itr;
    for(itr = MaterialList.begin();itr!=MaterialList.end();itr++)
    {
        if((*itr)->Name == name) return (Material*)(*itr);

    }

    return NULL;
}




void loadShaderInMateral(std::string name,std::string shaderPath)
{
    Material *currentMaterial;
    bool available =true;
     if(findMaterialtByName(name) == NULL)
     {
         MaterialList.push_back(new Material);
        currentMaterial = MaterialList.back();
        available = false;
     }
     else
     {
         currentMaterial = findMaterialtByName(name);
     }

    std::cout<<"Name of shader"<<shaderPath<<std::endl;
    std::cout<<"Name of shader"<<available<<std::endl;
    currentMaterial->Name =name;
     currentMaterial->FragmentShader = shaderPath +".fs";
     currentMaterial->VertexShader = shaderPath+".vs";
     currentMaterial->BuildShader();


}

 void setShader(Material * M,std::string shader, std::string shadersource)
{
    if(shader == "vertexshader")
    {
        M->VertexShader = shadersource;
    }
     else  if(shader == "fragmentshader")
    {
        M->FragmentShader = shadersource;
    }

    M->BuildShader();
}

void addMaterial(std::string name)
{
    if(findMaterialtByName(name)!= NULL) {addMaterial(name +".copy"); return; }

    MaterialList.push_back(new Material);
    MaterialList.back()->Name = name;
    MaterialList.back()->BuildShader();
    strcpy(MaterialName[MaterialList.size()-1] , name.c_str());
    std::cout<<std::string(MaterialName[MaterialList.size()-1])<<std::endl;
}
void assignMaterial(EngineObjects* obj, Material * mat)
{
    obj->RepresentngObject.mat = mat;

}

 void setMateriaColor(Material * mat,float x, float y, float z)
 {
     mat ->color = glm::vec3(x,y,z);

 }

 glm::vec3 getMaterialColor ( Material * mat)
 {
    return mat->color;

 }

 Texture* findTextureByName(std::string name)
 {
        std::vector<Texture*>::iterator itr;
        for (itr = TextureList.begin(); itr!= TextureList.end(); itr++ )
        {
            if((*itr)->Name  == name) {return (Texture*)(*itr); }
        }
        return NULL;
 }

 void addTexture(std::string name ,std::string location)
 {
     std::cerr << "laoding " << location << std::endl;
     if(findTextureByName(name) != NULL ){ addTexture(name + ".copy",location); return; }
     std::cerr << "new Texture: " << location << std::endl;
        TextureList.push_back(new Texture(location));
        TextureList.back()->Name = name;
        strcpy(TextureName[TextureList.size()-1], name.c_str());
        recalculateNameList();
    return ;
 }

 Texture* getTexture(Material*  name)
 {
     return name->texture;
 }
 void setTexture(Material* mat , Texture * tex)
 {
     mat->texture = tex;
 }


 void recalculateNameList()
 {
     int i=0;
     while(i<100 && i <MaterialList.size())
     {
         strcpy(MaterialName[i],MaterialList[i]->Name.c_str());
         i++;
     }

       i=0;
     while(i<100 && i <TextureList.size())
     {
         strcpy(TextureName[i],TextureList[i]->Name.c_str());
         i++;
     }

 }

//Light

extern setAmbientLightColor( float r,float g,float b)
{
   ambient.rgb.x=r;
   ambient.rgb.y=g;
   ambient.rgb.z=b;
}

extern setAmbientLightIntensity( float intensity)
{
    ambient.intensity = intensity;

}

//Getters

 PSvec3 getPosition(std::string name){ EngineObjects* obj= findObjectByName(name);  return{obj->RepresentngObject.transforms.getPosition().x,obj->RepresentngObject.transforms.getPosition().y,obj->RepresentngObject.transforms.getPosition().z};  }

 PSvec3 getRotation(std::string name){ EngineObjects* obj= findObjectByName(name);  return {obj->RepresentngObject.transforms.getRotation().x,obj->RepresentngObject.transforms.getRotation().y,obj->RepresentngObject.transforms.getRotation().z};  }
 PSvec3 getScale(std::string name){ EngineObjects* obj= findObjectByName(name);  return {obj->RepresentngObject.transforms.getScale().x,obj->RepresentngObject.transforms.getScale().y,obj->RepresentngObject.transforms.getScale().z}; }

 PSvec3 getPosition(EngineObjects* name){ EngineObjects* obj= name;  return{obj->RepresentngObject.transforms.getPosition().x,obj->RepresentngObject.transforms.getPosition().y,obj->RepresentngObject.transforms.getPosition().z};  }
 PSvec3 getRotation(EngineObjects* name){ EngineObjects* obj= name; return {obj->RepresentngObject.transforms.getRotation().x,obj->RepresentngObject.transforms.getRotation().y,obj->RepresentngObject.transforms.getRotation().z};}
 PSvec3 getScale(EngineObjects* name){EngineObjects* obj= name; return {obj->RepresentngObject.transforms.getScale().x,obj->RepresentngObject.transforms.getScale().y,obj->RepresentngObject.transforms.getScale().z};  }

 Material* getMaterial(std::string  name){ EngineObjects* obj= findObjectByName(name);  return obj->RepresentngObject.mat; }
 Material* getMaterial(EngineObjects* name){EngineObjects* obj= name; return obj->RepresentngObject.mat;  }



 int getShader(EngineObjects* name)
{
    if(name->RepresentngObject.mat->VertexShader  == "") {return 1;}
    else if(name->RepresentngObject.mat->VertexShader == "Resources/Phong.vs"){return 2;}
    else return 0;
}
 int getShader(std::string  name)
{
    if(findObjectByName(name)->RepresentngObject.mat->VertexShader  == "") {return 1;}
    else if(findObjectByName(name)->RepresentngObject.mat->VertexShader == "Phong.vs"){return 2;}
    else return 0;
}

//camera


void CameraRayCast ( GLFWwindow *window )
{
    currentCamera->setPosition(glm::vec3(0,0,0));
    double x,y;
    glfwGetCursorPos(window, &x, &y);
    std::cout << "x : "<<x<<"  y : "<<y<<std::endl;
    int height , width;
    glfwGetWindowSize(window,&width,&height);
    std::cout << "width  : "<<width<<"  height  : "<<height<<std::endl;

    double centerX = width/2.0;
    double centerY = height/2.0;

    float mouseX = (x- centerX)/ centerX;
    float mouseY = (centerY - y)/ centerY;
     std::cout << "currentcordX  : "<<mouseX<<"  currentcordY  : "<<mouseY<<std::endl;
      std::cout << "znear  : "<<currentCamera->getZnear()<<"  zfar  : "<<currentCamera->getZfar()<<std::endl;
     glm::vec4 homogenous = glm::vec4(mouseX,mouseY,-1 ,1);
     glm::mat4 inverseVIewAndProj = glm::inverse(currentCamera->getViewProjectionMat());
     glm::vec4 location= inverseVIewAndProj * homogenous;
     std::cout << "global locationX  : "<<location.x/location.w<<"  global locationY  : "<<location.y/location.w<< " global LocationZ :"<< location.z/location.w<<std::endl;
     glm::vec3 origin = glm::vec3 (location.x/location.w,location.y/location.w,location.z/location.w);

     std::vector<EngineObjects*>::iterator itr;
     std::vector<colliders*> colvector;
    for(itr = SceneObjects.begin();itr!=SceneObjects.end();itr++)
    {
       if((*itr)->collider != NULL)
       {
            colvector.push_back((*itr)->collider->collider);
       }

    }


    std::cout << "forward  : "<<currentCamera->Forward().x<<"  "<< currentCamera->Forward().y<<"   "<<currentCamera->Forward().z
    <<"  positin  : "<<currentCamera->Position().x<<"  "<<currentCamera->Position().y<<"   "<<currentCamera->Position().z<<std::endl;
    //Raycast  mouseCast(currentCamera->Position(),(origin-currentCamera->Position()),&colvector);
    Raycast  mouseCast(glm::vec3(0,0,0),origin,&colvector);
    colliders* buff  = (colliders*)mouseCast.cast();
    if(buff == NULL) return;
       for(itr = SceneObjects.begin();itr!=SceneObjects.end();itr++)
    {
        if((*itr)->collider != NULL)
       {if((*itr)->collider->collider == buff )
       {
            std::cout<<(*itr)->RepresentngObject.Name<<std::endl;
            selectedObject= (*itr);
       }}

    }



}

#endif // OPENGL3
