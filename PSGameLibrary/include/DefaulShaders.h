#ifndef DEFAULSHADERS_H_INCLUDED
#define DEFAULSHADERS_H_INCLUDED
#include<string>

const std::string DefaultVertexShader =
"#version 330 \n"
"in vec3  position;\n"
"in vec3  normal;\n"
"in vec2 UVCoord; \n"
"uniform mat4 ViewProjectionMat;\n"
"uniform mat4 ModelTransformMat; \n"
"void main() \n"
"{ \n"
"gl_Position = ViewProjectionMat*ModelTransformMat*vec4(position, 1.0); \n"
"}\n";


const std::string DefaultFragmentShader =
"#version 330 \n"

//"unifrom vec3  AmbientColor; \n"
//"uniform float AmbientStrenght;\n"

"void main()\n"
"{\n"
" gl_FragColor = vec4(0.6,0.4,0.1,1.0);\n"

"}\n";





#endif // DEFAULSHADERS_H_INCLUDED
