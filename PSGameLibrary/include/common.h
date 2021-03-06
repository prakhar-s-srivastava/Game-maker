#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED
#include<string>
#include<iostream>
#include<GL/glew.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<fstream>
#include<vector>
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<cstdlib>

static void Print(glm::vec3 vect , std::string name = "none")
{

    std::cout<<name<<"  " <<vect.x<<"  "<<vect.y<<"  "<<vect.z<<std::endl;
}
#endif // COMMON_H_INCLUDED
