#include <sDebugging.hpp>

namespace shb{

void log(const char* msg){
  if(DEBUG){
    std::cout<< msg;
  }
}
void log(const std::string& msg){
  if(DEBUG){
    std::cout<< msg;
  }
}
void log(double& msg){
  if(DEBUG){
    std::cout<< msg;
  }
}


GLenum checkError(const char *file, int line, const std::string& location)
{
  if(DEBUG){
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::cout<< location << "\n";
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
  }
  return -1;
}



}//namespace shb