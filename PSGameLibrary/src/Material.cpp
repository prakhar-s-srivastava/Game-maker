#include "PSGameLibrary.h"
#include "DefaulShaders.h"

OpenGL3::Material::Material()
{
    //BuildShader();
}

OpenGL3::Material::~Material()
{
    glDeleteProgram(ShaderProgram);

}
bool OpenGL3::Material:: BuildShader()
{
    glDeleteProgram(ShaderProgram);
    const char  *vss [1];
    const char  *fss [1];
    int length[1];
    GLsizei vsi,fsi;
    GLchar VsLog[1000] ,FsLog[1000];
    GLint errorVs,errorFs;
    GLuint vs,fs;
     vs = glCreateShader(GL_VERTEX_SHADER);//Generated VretexShader
    fs = glCreateShader(GL_FRAGMENT_SHADER);//generated fragment Shader
    std::cout<<"Shaders Created"<<std::endl;
    std::string VerxtexShaderSource,FragmentShaderSource;


    if(FragmentShader.empty()) // Checking if we need to use defaultShader
    {

        VerxtexShaderSource=DefaultVertexShader;
        FragmentShaderSource = DefaultFragmentShader;
    }
    else{
        VerxtexShaderSource = LoadShader(VertexShader);
        FragmentShaderSource=LoadShader(FragmentShader);
    }
    std::cout<<"Shaders Source obtained"<<std::endl;

    vss[0] = VerxtexShaderSource.c_str();/////////////////
    length[0] =VerxtexShaderSource.length();////////////  Vertex Shader Source set;
    glShaderSource(vs,1,vss,length);///

    fss[0] = FragmentShaderSource.c_str();/////////////////
    length[0] =FragmentShaderSource.length();////////////  Vertex Shader Source set;
    glShaderSource(fs,1,fss,length);///

    std::cout<<"Shaders Souces Sent to GPU"<<std::endl;

    glCompileShader(vs);////Compiling shader
    glCompileShader(fs);///

    std::cout<<"Shaders copiled"<<std::endl;

    glGetShaderiv(vs,GL_COMPILE_STATUS,&errorVs);// Checking for compiled shader
    glGetShaderiv(fs,GL_COMPILE_STATUS,&errorFs);//

    if(errorFs  != GL_TRUE || errorVs != GL_TRUE)  //Getting Log Of shader Compilation
    {
        std::cout<<"Shaders copmilation Error"<<std::endl;
        glGetShaderInfoLog(vs, sizeof(VsLog), &vsi, VsLog);
        glGetShaderInfoLog(vs, sizeof(FsLog), &fsi, FsLog);
        std::cout<<"Vertex Error:"<<VsLog<<std::endl;

        std::cout<<"Fragment Error:"<<VsLog<<std::endl;
        return false;
    }


    ShaderProgram =glCreateProgram(); // Defining Shader program
    glAttachShader(ShaderProgram,vs);//attach Vetex Shader
    glAttachShader(ShaderProgram,fs);//attach Fragment Shader
     std::cout<<"Shaders Program Created"<<std::endl;

    glBindAttribLocation(ShaderProgram, 0, "position");
	glBindAttribLocation(ShaderProgram, 1, "normal");
	glBindAttribLocation(ShaderProgram, 2, "UVCoord");
     std::cout<<"Shaders Program Attrib binded"<<std::endl;


    glLinkProgram(ShaderProgram);  //Combining both the shaders
    glValidateProgram(ShaderProgram); // valaditing the program
     std::cout<<"Shaders Program validated"<<std::endl;


	glDeleteShader(vs);
    glDeleteShader(fs);
    return true;
}



void OpenGL3::Material::bindShader(Transform *trans )
{

    glUseProgram(ShaderProgram);
    GLuint ViewProjectionMatrix=glGetUniformLocation(ShaderProgram,"ViewProjectionMat");
    glUniformMatrix4fv(ViewProjectionMatrix,1,GL_FALSE,&currentCamera->getViewProjectionMat()[0][0]);
    GLuint ModelTransformMat = glGetUniformLocation(ShaderProgram,"ModelTransformMat");
    glUniformMatrix4fv(ModelTransformMat,1,GL_FALSE,&trans->getModelTransformMat()[0][0]);
    glUniform3f(glGetUniformLocation(ShaderProgram,"color"),color.x,color.y , color.z);
    setAmbientLight();
    setDirectionLight();
    if(texture != NULL) {texture->bindTexture(); }

}
void OpenGL3::Material::unbindShader()
{
    glUseProgram(0);
}





std::string  OpenGL3::Material::LoadShader(std::string  &shaderLocation)
{
     std::ifstream file;
    file.open((shaderLocation).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << shaderLocation << std::endl;
    }

    return output;
}


bool OpenGL3::Material:: setAmbientLight()
{
    glUniform3f(glGetUniformLocation(ShaderProgram,"ambient.rgb"),ambient.rgb.x,ambient.rgb.y,ambient.rgb.z);
    glUniform1f(glGetUniformLocation(ShaderProgram,"ambient.intensity"),ambient.intensity);
}
bool OpenGL3::Material::setDirectionLight()
{
    std::vector<DirectionalLight>::iterator itr;
    int it=0;
    for(itr = directionalLights.begin();itr!=directionalLights.end();itr++)
    {
        std::string  finder;
        //finder = std::to_string(it);
        finder = "directionalLights[" +std::to_string(it)+"]";
       // std::cout<<(*itr).color.x<<std::endl;
        glUniform3f(glGetUniformLocation(ShaderProgram,std::string(finder+".position").c_str()),(*itr).position.x,(*itr).position.y,(*itr).position.z);
        glUniform3f(glGetUniformLocation(ShaderProgram,std::string(finder+".direction").c_str()),(*itr).direction.x,(*itr).direction.y,(*itr).direction.z);
        glUniform3f(glGetUniformLocation(ShaderProgram,std::string(finder+".color").c_str()),(*itr).color.x,(*itr).color.y,(*itr).color.z);
        glUniform1f(glGetUniformLocation(ShaderProgram,std::string(finder+".intensity").c_str()),(*itr).intensity);
        it++;
    }
}


