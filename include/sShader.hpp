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
#include <sDebugging.hpp>

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

class sShader{
 public:
  sShader(){};

  sShader(
    GLenum type, 
    const std::string& fp, 
    bool compileOnCreation = true, 
    bool setSourceOnCreation = true
  );

  void setSource(const char* source = "shark"); //associates source code with a shader handle
  void compile(); //compiles shader
  void deleteShader(); //handles deletion
  void handleErrors(); //handles errors

  //getters
  GLuint handle() { return m_Handle; }
  std::string readFile(const std::string& filePath);


 private:
  GLuint m_Handle = 0;
  const char* m_Source = nullptr;
  std::string m_Code;
  std::string path{"../shaders/"};

};


class sShaderProgram{
 public:
  sShaderProgram(){
    m_ProgramName = "uninitialised";
  };

  sShaderProgram(const char* name, std::vector<sShader> shaders);
  void addShaders(std::vector<GLuint> shaders);
  void addShader(GLuint shader);
  void linkProgram();
  void useProgram();
  void deleteShaderProgram();

  const GLuint& handle() const{ 
    return m_Handle; 
  }

  const char* name() { 
    return m_ProgramName.c_str(); 
  }

 private:
  std::string m_ProgramName = "";
  GLuint m_Handle;
};



}//namespace shb