#include"Export.h"
#include"json.hpp"

using  json::JSON;

bool ExportScene()
{
    JSON objects;
    JSON materials;
    JSON textures;
    JSON exportJson;
    mkdir("Export");
    FILE *exportFIle;
    exportFIle=fopen("Export/exportFile.json","w");
    if(exportFIle == NULL){puts("Cant Open");}
    {
        exportJson["objectList-size"] = SceneObjects.size();
        for(int it =0;it<SceneObjects.size();it++)
        {
            objects[it]["name"] ="Export: "+SceneObjects[it]->RepresentngObject.Name;
            objects[it]["type"] = (int)SceneObjects[it]->Type;
            objects[it]["source"] = SceneObjects[it]->RepresentngObject.Name != ""?getFileName(SceneObjects[it]->RepresentngObject.getsourceFile().c_str()):"none";
            mkdir("Export/Resources");

            {
                std::string newsourcelocation = "Export/Resources/"+std::string(getFileName(SceneObjects[it]->RepresentngObject.getsourceFile().c_str()));
                 FILE *newSourceFIle =fopen(newsourcelocation.c_str(),"r");
                 if(newSourceFIle ==NULL){
                copyFIle(SceneObjects[it]->RepresentngObject.getsourceFile(),
                "Export/Resources",getFileName(SceneObjects[it]->RepresentngObject.getsourceFile().c_str()));

                 }
                fclose(newSourceFIle);
            }
                                                                                                //copied source file*


            objects[it]["position"] = json::Array(getPosition(SceneObjects[it]).x,getPosition(SceneObjects[it]).y,getPosition(SceneObjects[it]).z);
            objects[it]["rotation"] = json::Array(getRotation(SceneObjects[it]).x,getRotation(SceneObjects[it]).y,getRotation(SceneObjects[it]).z);
            objects[it]["scale"] = json::Array(getScale(SceneObjects[it]).x,getScale(SceneObjects[it]).y,getScale(SceneObjects[it]).z);
            objects[it]["material"] = "Export: "+SceneObjects[it]->RepresentngObject.mat->Name;

            if(SceneObjects[it]->collider != NULL)                                  //export collider
            {
                 if(SceneObjects[it]->collider->collider->Type  ==  colliders::ColliderType::BOXAABB)
                 {
                     objects[it]["collider"]["type"] = "BOXAABB";
                     boxAABB *temp = (boxAABB*) SceneObjects[it]->collider->collider;
                     objects[it]["collider"]["max"] = json::Array(temp->maxX,temp->maxY,temp->maxZ);
                     objects[it]["collider"]["min"] = json::Array(temp->minX,temp->minY,temp->minZ);
                 }

            }




        }


        copyFIle("Resources/Phong.vs","Export/Resources","Phong.vs");
        copyFIle("Resources/Phong.fs","Export/Resources","Phong.fs");



        exportJson["materialList-size"] = MaterialList.size();
        for(int it =0;it<MaterialList.size();it++)
        {
            materials[it]["name"] = "Export: "+ MaterialList[it]->Name;
            materials[it]["vertex-shader"] = std::string ("Export/Resources/"+std::string(getFileName(MaterialList[it]->VertexShader.c_str())));
            materials[it]["fragment-shader"] = std::string ("Export/Resources/"+std::string(getFileName(MaterialList[it]->FragmentShader.c_str())));
            materials[it]["color"] = json::Array(MaterialList[it]->color.x,MaterialList[it]->color.y,MaterialList[it]->color.z );
            materials[it]["texture"] = MaterialList[it]->texture != NULL? "Export: "+MaterialList[it]->texture->Name : "Export: ";
        }

        exportJson["textureList-size"] = TextureList.size();
        for(int it =0;it<TextureList.size();it++)
        {
                textures[it]["name"] = "Export: "+TextureList[it]->Name;
                textures[it]["source"]=TextureList[it]->getLocation();
                copyFIleBinary(TextureList[it]->getLocation(),"Export/Resources",std::string(getFileName(TextureList[it]->getLocation().c_str())));

        }

        exportJson["textures"]= textures;
        exportJson["objects"] = objects;
        exportJson["materials"] = materials;
    }

    fputs(exportJson.dump().c_str(),exportFIle);
    fclose(exportFIle);

    std::cout<<exportJson<<std::endl;
}


bool ImportScene(std::string filelocation)
 {

    FILE *jsonFile = fopen(filelocation.c_str(),"r");
    char  data[4096] ={'\0'};

    while (!feof(jsonFile))
    {
        char c[2]={'\0'};
         c[0]= fgetc(jsonFile);
        if(feof(jsonFile)) break;
        strcat(data,c);

    }
    std::cout <<data<<std::endl;

    JSON importJson =JSON::Load(std::string(data));
    JSON numObjects,numMaterials,numTextures;
    numObjects = importJson["objectList-size"];
    numMaterials = importJson["materialList-size"];
    numTextures = importJson["textureList-size"];



    for(int it =0;it<numTextures.ToInt();it++)
    {
        addTexture(importJson["textures"][it]["name"].ToString(),importJson["textures"][it]["source"].ToString());

    }



    for(int it =0;it<numMaterials.ToInt();it++)
    {
        addMaterial(importJson["materials"][it]["name"].ToString());
       MaterialList.back()->VertexShader =importJson["materials"][it]["vertex-shader"].ToString();
       MaterialList.back()->FragmentShader =importJson["materials"][it]["fragment-shader"].ToString();
       MaterialList.back()->BuildShader();
       setMateriaColor(MaterialList.back(),importJson["materials"][it]["color"][0].ToFloat(),importJson["materials"][it]["color"][1].ToFloat(),
       importJson["materials"][it]["color"][2].ToFloat());
       setTexture(MaterialList.back(),findTextureByName(importJson["materials"][it]["texture"].ToString()));
    }




    for(int it =0;it<numObjects.ToInt();it++)
    {
        addObject( importJson["objects"][it]["name"].ToString(),
                  "Export/Resources/"+std::string(getFileName(SceneObjects[it]->RepresentngObject.getsourceFile().c_str())));
        setPosition(SceneObjects.back(),importJson["objects"][it]["position"][0].ToFloat(),importJson["objects"][it]["position"][1].
                    ToFloat(),importJson["objects"][it]["position"][2].ToFloat());
        setRotation(SceneObjects.back(),importJson["objects"][it]["rotation"][0].ToFloat(),importJson["objects"][it]["rotation"][1].
                    ToFloat(),importJson["objects"][it]["rotation"][2].ToFloat());
        setScale(SceneObjects.back(),importJson["objects"][it]["scale"][0].ToFloat(),importJson["objects"][it]["scale"][1].
                    ToFloat(),importJson["objects"][it]["scale"][2].ToFloat());
        assignMaterial(SceneObjects.back(),findMaterialtByName(importJson["objects"][it]["material"].ToString()));
    }





    return true;
 }
