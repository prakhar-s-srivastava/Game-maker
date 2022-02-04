#ifndef OPENGL3_0RENDERER_H_INCLUDED
#define OPENGL3_0RENDERER_H_INCLUDED

#include<PSGameLibrary.h>
#include<Gl/glew.h>
#include<string>

extern std::vector<Object*> SceneObjects;

extern void addObject(std::string location = "");
 extern void renderScene();




#endif // OPENGL3_0RENDERER_H_INCLUDED
