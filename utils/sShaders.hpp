#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include <glad/glad.h>

namespace shb{

class sShaders{
 public:
    sShaders(int type){
        m_Handle = glCreateShader(type);

        
    }
   
 public:
    const char* m_Code{};
    
    GLuint m_Handle;
    std::string m_FilePath{};

};







}//namespace shb