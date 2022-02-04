#include"headers.h"
#include"fileBrowser.h"
#include"import.h"
#include"Export.h"
#include"Physics.h"

//#include "ItemList.h"


int main( int argc , char** argv)
{

// glew and glfw inilizer
     glfwInit();
     const GLFWvidmode *mode=glfwGetVideoMode(glfwGetPrimaryMonitor());
     GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "PSGAMEMAKER", NULL, NULL);

        glfwMakeContextCurrent(window);
        GLenum glewSatus = glewInit();
      if(glewSatus != GLEW_OK) std::cerr<<"Glew not initialized"<<std::endl;
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glEnable(GL_DEPTH_TEST);
//screen height n widht



initilize();
addObject("a","./Resources/untitled.obj");
setPosition("a",0,0,5);
addMaterial("Default");
assignMaterial(findObjectByName("a"),findMaterialtByName("Default"));
addTexture("textureDefault","");


//getting imgui ready
       IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
        const char glsl_version[15] = "#version 130";
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);


        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glViewport(5, 5, mode->width-10, mode->height-10);

        //imgui assets
        mkdir("AssetFolder");
        pathlist.push_back("AssetFolder/");
        browseFiles("AssetFolder/");

        //                                                                                                                                  Test Section



        //                                                                                                                                  test Section

    double last =0;
    double now,delta;
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            last =glfwGetTime();
            renderScene();
            now = glfwGetTime();
            delta = now - last;

            if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                CameraRayCast(window);
            }


        //Code
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


    {

        ImGui::Begin("fps");
        ImGui::Text( std::to_string(1/delta).c_str());
        ImGui::End();
        if(ImGui::BeginMainMenuBar())                                                                               //Menu
        {
                if(ImGui::BeginMenu("File"))                                                                       //file
                {
                    ImGui::MenuItem("Open");
                    ImGui::EndMenu();

                }
                  if(ImGui::BeginMenu("Edit"))                                                                  //edit
                {
                    ImGui::MenuItem("Open");
                    ImGui::EndMenu();

                }

                  if(ImGui::BeginMenu("Add"))                                                           //add
                {
                    if(ImGui::BeginMenu("Light"))
                    {
                        if(ImGui::MenuItem("Ambient")){ if(ambient.intensity == 0){ addAmbient(); }}
                        if(ImGui::MenuItem("Directional")){ addDirectionalLight();}
                        if(ImGui::MenuItem("point")){}
                        ImGui::EndMenu();
                    }
                   if(ImGui::MenuItem("Material"))
                   {
                       addMaterial("material");
                   }
                    ImGui::EndMenu();

                }


                     if(ImGui::BeginMenu("Export"))                                                                  //Export
                {
                    if(ImGui::MenuItem("Scene")){ ExportScene();}
                    ImGui::EndMenu();

                }
                ImGui::EndMainMenuBar();

        }
        }


        ImGui::Begin("ItemList");                                                                                                    //Item LISTS
        ImGui::ListBoxHeader("Objects",SceneObjects.size(),30);
        std::vector<EngineObjects*>::iterator itr;
        for(itr = SceneObjects.begin();itr!=SceneObjects.end();itr++)
        {
            if( ImGui::Selectable((*itr)->RepresentngObject.Name.c_str(),false))
            {
               selectedObject = *itr;
            }
        }
        ImGui::ListBoxFooter();
        ImGui::End();                                                                                                                               //item lists




            {
            ImGui::Begin("Properties");
                 if(selectedObject!=NULL){                                                                                             //Properties
                char name[50];
                strcpy(name , selectedObject->RepresentngObject.Name.c_str());
                if(ImGui::InputText("Name",&name[0],50))
                {
                    selectedObject->RepresentngObject.Name = std::string(name);
                }

           float position[3] ={0,0,0};
             if(selectedObject != NULL){
           position[0] = getPosition(selectedObject).x;
            position[1] = getPosition(selectedObject).y;
            position[2] = getPosition(selectedObject).z;
             }
            if(ImGui::InputFloat3("Position",position,"%.3f"))
            {
                if(selectedObject != NULL)
                {
                    setPosition(selectedObject,position[0],position[1],position[2]);
                }
            }



             float rotation[3]={0,0,0};
             if(selectedObject != NULL){
           rotation[0] = getRotation(selectedObject).x;
            rotation[1] = getRotation(selectedObject).y;
            rotation[2] = getRotation(selectedObject).z;
             }
            if(ImGui::InputFloat3("Rotation",rotation,"%.3f"))
            {
                if(selectedObject != NULL)
                {
                    setRotation(selectedObject,rotation[0],rotation[1],rotation[2]);
                }
            }



             float scale[3]={0,0,0};
             if(selectedObject != NULL){
            scale[0] = getScale(selectedObject).x;
            scale[1] = getScale(selectedObject).y;
            scale[2] = getScale(selectedObject).z;
             }
            if(ImGui::InputFloat3("Scale",scale,"%.3f"))
            {
                if(selectedObject != NULL)
                {
                    setScale(selectedObject,scale[0],scale[1],scale[2]);
                }
            }


             int materialname =0;
             char *namesbuff[100] ;
             if(selectedObject != NULL){

                for (int it =0;it<100;it++)
                {
                    namesbuff[it] = MaterialName[it];
                    if(!strcmp(MaterialName[it],getMaterial(selectedObject)->Name.c_str()))
                    {
                        materialname =it;
                    }
                }
             }
            char **names =namesbuff;
            if (ImGui::Combo("material",&materialname,names,MaterialList.size()) && selectedObject != NULL)
            {
                    assignMaterial(selectedObject,findMaterialtByName(std::string(MaterialName[materialname])));
                    recalculateNameList();
            }

            static const char* Items[] = {"none","Default","Standard"};
            int choice=0;
            if(selectedObject != NULL)choice = getShader(selectedObject);

            if(ImGui::Combo("Shader",&choice,Items,IM_ARRAYSIZE(Items)) && selectedObject != NULL)
            {
                if(choice == 1)
                {
                    setShader(selectedObject->RepresentngObject.mat,"vertexshader","");
                    setShader(selectedObject->RepresentngObject.mat,"fragmentshader","");
                }
                else if(choice ==2)
                {
                      setShader(selectedObject->RepresentngObject.mat,"vertexshader","Resources/Phong.vs");
                        setShader(selectedObject->RepresentngObject.mat,"fragmentshader","Resources/Phong.fs");
                }
            }

            {
                float color[3]; color[0] = getMaterialColor(getMaterial(selectedObject)).x ;
                color[1] = getMaterialColor(getMaterial(selectedObject)).y ; color[2] = getMaterialColor(getMaterial(selectedObject)).z;
                if(ImGui::ColorEdit3("Material Color ",color))
                {
                    setMateriaColor(getMaterial(selectedObject),color[0],color[1],color[2]);
                }
            }


              if(selectedObject->Type   == AMBIENTLIGHT)
                 {
                        float colora[3]; colora[0] =ambient.rgb.x;colora[1] =ambient.rgb.y;colora[2]=ambient.rgb.z;
                        ImGui::ColorEdit3("Color", colora);
                        selectedObject->setColor((colora[0]),(colora[1]),(colora[2] ));

                        float intensity = ambient.intensity;
                        if(ImGui::InputFloat("intensity",&intensity,0.01,0.1))
                        {
                            ambient.intensity=intensity;
                        }
                 }

                 if(selectedObject->Type == DIRECTIONALLIGHT)
                 {
                        float colors[3]; colors[0] = selectedObject->getColor().x;colors[1] = selectedObject->getColor().y;colors[2] = selectedObject->getColor().z;
                        if(ImGui::ColorEdit3("Color", colors))
                        {
                        selectedObject->setColor((colors[0]),(colors[1]),(colors[2] ));
                        }

                          float intensity = selectedObject->getIntensity();
                          if(ImGui::InputFloat("intensity",&intensity,0.01,0.1))
                        {
                            selectedObject->setIntense(intensity);
                        }

                        float direction[3];direction[0] = selectedObject->getDirection().x;direction[1]=selectedObject->getDirection().y;direction[2] = selectedObject->getDirection().z;
                        if(ImGui::InputFloat3("direction",direction))
                        {
                                selectedObject->setDirection(direction[0],direction[1],direction[2]);
                        }

                 }

                    {


                    char *buffchar[100];
                    int num =0;
                    for(int it =0 ;it<100;it++)
                    {
                        buffchar[it] =TextureName[it];

                        if(getTexture(getMaterial(selectedObject)) != NULL)
                {
                        if(!strcmp(getTexture(getMaterial(selectedObject))->Name.c_str(),TextureName[it])){num =it;}
                }
                    }
                    char **names =buffchar;
                    if(ImGui::Combo("texture",&num,names,TextureList.size()))
                    {
                        recalculateNameList();
                        std::cout<<"tx number " <<num<<"  "<< std::string(TextureName[num])<<"end"<<std::endl;
                        setTexture(getMaterial(selectedObject),findTextureByName(std::string(TextureName[num])));

                    }
                    }

                 }
            ImGui::End();
        }                                                                                                                                                                            //Properties;




        {

            ImGui::Begin("Asset Manager");

                   //std::vector<char*>::iteratir
               if(ImGui::Button("back"))
               {
                   if(pathlist.back() != "AssetFolder/")
                   {
                       pathlist.pop_back();
                       browseFiles(listToString().c_str());
                   }
               }


            ImGui::PushID(1);                                                                                                                              //List Directories
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.6f, 0.6f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.3f, 0.7f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.06f, 0.8f, 0.8f));
            std::vector<std::string>::iterator itr;
             directoriesDisplay=directories;
            unsigned int colnumber= 0;
            for(itr = directoriesDisplay.begin();itr != directoriesDisplay.end();itr++)
            {
               if( colnumber>0 && colnumber<length){ ImGui::SameLine(0,ImGui::GetStyle().ItemInnerSpacing.x);}
               else{colnumber =0;}
                colnumber++;
                if(ImGui::Button((*itr).c_str(),ImVec2(100,100)))
                {
                    pathlist.push_back((*itr)+"/");
                    browseFiles(listToString().c_str());
                }
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();                                                                                                                                                            //List Directories


            ImGui::PushID(2);                                                                                                                                                              //List Files
            ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.3f, 0.3f, 0.3f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.3f, 0.7f, 0.3f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.8f, 0.8f, 0.8f));
            filesDisplay =files;
             colnumber= 0;
            for(itr = filesDisplay.begin();itr != filesDisplay.end();itr++)
            {
               if( colnumber>0 && colnumber<length){ ImGui::SameLine(0,ImGui::GetStyle().ItemInnerSpacing.x);}
               else{colnumber =0;}
                colnumber++;
                if(ImGui::Button((*itr).c_str(),ImVec2(100,100)))
                {
                       import((listToString() + (*itr)).c_str());

                }
            }
            ImGui::PopStyleColor(3);
            ImGui::PopID();                                                                                                                                                                                   //List Files




            ImGui::End();
        }







        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
