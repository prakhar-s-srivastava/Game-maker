#include"Texture.h"
#include"stb_image.h"
namespace OpenGL3{
Texture::Texture(std::string location)
{
    std::cerr << "Loading Texture " << location << std::endl;
    glDeleteTextures(1,&textureBuffer);
    int width, height, numComponents;
    unsigned char* data = stbi_load((location).c_str(), &width, &height, &numComponents, 4);
    textureLocation = location;

    if(data == NULL)
		std::cerr << "Unable to load texture: " << location << std::endl;

    glGenTextures(1, &textureBuffer);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

Texture::~Texture()
{
      glDeleteTextures(1,&textureBuffer);
}

void Texture::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D,textureBuffer);
}

 void  Texture::loadTexture(std::string location)
 {
      glDeleteTextures(1,&textureBuffer);
    int width, height, numComponents;
    unsigned char* data = stbi_load((location).c_str(), &width, &height, &numComponents, 4);
    textureLocation = location;

    if(data == NULL)
		std::cerr << "Unable to load texture: " << location << std::endl;

    glGenTextures(1, &textureBuffer);
    glBindTexture(GL_TEXTURE_2D, textureBuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
 }

 std::string  Texture::getLocation()
 {
     return textureLocation;
 }

}
