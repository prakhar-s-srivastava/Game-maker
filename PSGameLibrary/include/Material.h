#ifndef MATERIAL_H
#define MATERIAL_H
#include"common.h"
#include"Transform.h"
#include"Lighting.h"
#include"Texture.h"

namespace OpenGL3{
class Material
{
    public:
        Material();
        virtual ~Material();
        bool BuildShader();
        void bindShader(Transform *trans );
        void unbindShader();


        //Variables
        std::string FragmentShader;
        std::string VertexShader;
        std::string Name="";
        glm::vec3 color = glm::vec3(1.0,1.0,1.0);
        Texture *texture = NULL;
    protected:

    private:
        std::string LoadShader(std::string &shaderLocation);
        bool isTextured =false;
        GLuint ShaderProgram=0;
        bool setAmbientLight( );
        bool setDirectionLight();

};
}
#endif // MATERIAL_H
