#ifndef OBJECTIMPORT_H
#define OBJECTIMPORT_H
#include"common.h"

class ObjectImport
{
    public:
        ObjectImport();
        virtual ~ObjectImport();
        void loadfromfile(const std::string objectLocation);
        std::vector<glm::vec3> positionData;
        std::vector<glm::vec3> normalData;
        std::vector<glm::vec3> indexData;
        std::vector<glm::vec2> texCoordData;

    protected:

    private:
};

#endif // OBJECTIMPORT_H
