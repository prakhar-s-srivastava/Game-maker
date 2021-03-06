#include "PSGameLibrary.h"

ObjectImport::ObjectImport()
{

}

ObjectImport::~ObjectImport()
{
    //dtor
}

void ObjectImport::loadfromfile(const std::string objectLocation)
{

    //VARIABLES
    positionData.clear();
    normalData.clear();
    texCoordData.clear();
    indexData.clear();
    std::vector<glm::vec3> positionDataT;
    std::vector<glm::vec3> normalDataT;
    std::vector<glm::vec3> indexDataT;
    std::vector<glm::vec2> texCoordDataT;
    std::vector<GLuint> positionindices, normalIndices, texIndices;
    std::string line;
    std::ifstream file((objectLocation).c_str());

    //FUNCTIONS
    if(file.is_open())
    {
        while(!file.eof())
        {
            std::getline(file,line);
            if(line[0]=='v' && line[1]!='n' && line[1]!='t')
            {
                glm::vec3 position;
                char temp1[4];
                sscanf(line.c_str(), "%c %f %f %f\n", temp1,&position.x, &position.y, &position.z );
               // std::cout<<"v "<<position.x<<" "<<position.y<<" "<<position.z<<std::endl;
                positionDataT.push_back(position);
            }
            else if(line[0]=='v' && line[1]=='t')
            {
                glm::vec2 texCoordTemp;
                char temp2[4];
                sscanf(line.c_str(),"%s %f %f\n",temp2,&texCoordTemp.x,&texCoordTemp.y);
               // std::cout<<"vt "<<texCoordTemp.x<<" "<<texCoordTemp.y<<std::endl;
                texCoordDataT.push_back(texCoordTemp);

            }
            else if(line[0]=='v' && line[1]=='n')
            {
                glm::vec3 normalTemp;
                char temp3[4];
                sscanf(line.c_str(),"%s %f %f %f\n",temp3,&normalTemp.x,&normalTemp.y,&normalTemp.z);
               // std::cout<<"vn "<<normalTemp.x<<" "<<normalTemp.y<<" "<<normalTemp.z<<std::endl;
                normalDataT.push_back(normalTemp);
            }
            else if(line[0]=='f')
            {
                GLuint positionIndex[3],normalIndex[3],texIndex[3];
                char temp4[4];
                int collected  = sscanf(line.c_str(),"%c %d/%d/%d %d/%d/%d %d/%d/%d\n",
                temp4,&positionIndex[0],&texIndex[0],&normalIndex[0],
                &positionIndex[1],&texIndex[1],&normalIndex[1],
                &positionIndex[2],&texIndex[2],&normalIndex[2]);
                //std::cout<<"f "<<positionIndex[0]<<"/"<<texIndex[0]<<"/"<<normalIndex[0]<<" "<<
                //positionIndex[1]<<"/"<<texIndex[1]<<"/"<<normalIndex[1]<<" "<<
                //positionIndex[2]<<"/"<<texIndex[2]<<"/"<<normalIndex[2]<<std::endl;
                if(collected != 10)std::cout<<"cannot load Obj"<<std::endl;

                for(int i =0;i<3;i++){
                positionindices.push_back(positionIndex[i]);
                texIndices.push_back(texIndex[i]);
                normalIndices.push_back(normalIndex[i]);
                }
            }
            else
            {
                continue;
            }

            //else if()
        }
    }

    else
    {
        std::cerr<<"could not load "<<objectLocation<<std::endl;
    }
    for(unsigned int i=0;i<positionindices.size();i++)
    {
        GLuint positionIndex=positionindices[i];
        glm::vec3 pos = positionDataT[positionIndex-1];
        positionData.push_back(pos);

    }

    for(int i=0;i<texIndices.size();i++)
    {
        GLuint texIndex=texIndices[i];
        glm::vec2 texCoord = texCoordDataT[texIndex-1];
        texCoordData.push_back(texCoord);

    }

    for (int i=0;i<normalIndices.size();i++)
    {
        GLuint normalIndex =normalIndices[i];
        glm::vec3 normal = normalDataT[normalIndex-1];
        normalData.push_back(normal);

    }

    file.close();
    std::cout<<"OBJ loaded"<<std::endl;

}
