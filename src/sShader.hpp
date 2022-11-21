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
    sShader(const shb::sShader &) = delete;

    sShader(
        int type, 
        const std::string& fp, 
        bool compileOnCreation, 
        bool setSourceOnCreation
        );

    void setSource(const char* source = "shark"); //associates source code with a shader handle
    void compile(); //compiles shader
    void deleteShader(); //handles deletion
    void handleErrors(); //handles errors

    //getters
    GLuint handle() { return m_Handle; }

 private:
    GLuint m_Handle;
    const char* m_Source;
    std::vector<char> m_Code;

};



}//namespace shb