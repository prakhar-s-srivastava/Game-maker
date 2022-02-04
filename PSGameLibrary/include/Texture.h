#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include"common.h"

namespace OpenGL3{
class Texture
{
    public:
    Texture(std::string location = "");
    ~Texture();
    void bindTexture();
    void loadTexture(std::string location);
    std::string  getLocation();
    std::string Name = "Default";
    private:
    GLuint textureBuffer;
    std::string textureLocation="";

};
}
#endif // TEXTURE_H_INCLUDED
