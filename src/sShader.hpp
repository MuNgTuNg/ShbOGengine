#pragma once

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
std::string readFile(const char *filePath);


class sShader{
 public:
    //sShader(const shb::sShader &) = delete;
    sShader(){};
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
    GLuint& handle() { return m_Handle; }
    std::string readFile(const char *filePath);


 private:
    GLuint m_Handle = 0;
    const char* m_Source = nullptr;
    std::string m_Code;

};


//needs a GLUInt handle
//vector of handles to shaders that takes an initialiser list
//link program function
class sShaderProgram{
 public:
    void init();
    sShaderProgram(){
      m_ProgramName = "uninitialised";
    };
    sShaderProgram(const char* name);

    void addShaders(std::vector<GLuint> shaders);

    void addShader(sShader& shader);

    void linkProgram();

    void useProgram();

    const GLuint& handle() const { return m_Handle; }

    void deleteShaderProgram();

    const char * name() { return m_ProgramName.c_str(); }
 public:
    std::string m_ProgramName = "";
    GLuint m_Handle;


};



}//namespace shb