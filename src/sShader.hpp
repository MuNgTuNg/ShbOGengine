//std
#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>

//unix
#include <filesystem>

//GL
#include <glad/glad.h>

//mine 
#include <sUtils.hpp>

/*
    »»»SHADER CLASS«««
     •encapsulates shader functionality such as:
      creation
      destruction
      compilation
      error handling
      setting and relating source code to shader handles
*/

namespace shb{


std::vector<char> createShaderSource(const std::string& filePath);

class sShader{
 public:
    //sShader(const shb::sShader &) = delete;

    sShader(
        int type, 
        const std::string& fp, 
        bool compileOnCreation = true, 
        bool setSourceOnCreation = true
        );

    void setSource(const char* source = "shark"); //associates source code with a shader handle
    void compile(); //compiles shader
    void deleteShader(); //handles deletion
    void handleErrors(); //handles errors

    //getters
    const GLuint& handle() const { return m_Handle; }

 private:
    GLuint m_Handle;
    const char* m_Source;
    std::vector<char> m_Code;

};


//needs a GLUInt handle
//vector of handles to shaders that takes an initialiser list
//link program function
class sShaderProgram{
 public:
    sShaderProgram(const char* name);

    void addShaders(std::vector<GLuint> shaders);

    void addShader(sShader& shader);

    void linkProgram();

    void useProgram();

    const GLuint& handle() const { return m_Handle; }

    void deleteShaderProgram();

    const char * name() { return m_ProgramName.c_str(); }
 public:
    std::string m_ProgramName;
    GLuint m_Handle;


};



}//namespace shb