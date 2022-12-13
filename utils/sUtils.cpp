#include <sUtils.hpp>

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


GLenum checkError(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
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



std::vector<char> readFile(const std::string& filePath){
 //open file at the end of the file (ate) in binary form, and open for input
  char* cwd = get_current_dir_name();

  std::ifstream file;
  file.open(filePath.c_str(), std::ios::ate |  std::ios::binary | std::ios::in );

 //check file is open
  // if(!file.is_open()){
  //    DEBUGLOG("Failed to open file: ");
  //    DEBUGLOG(filePath.c_str());
  //    DEBUGLOG("\n at:");
  //    DEBUGLOG(cwd);
  //    DEBUGLOG("\n");
  //   }
  // else{
  //    DEBUGLOG("Successfully opened file: ");
  //    DEBUGLOG(filePath.c_str());
  //    DEBUGLOG("\n at:");
  //    DEBUGLOG(cwd.);
  //    DEBUGLOG("\n");   
  //    }

 //save size of file, pointer is at the end of file 
  int size = file.tellg();
  
 //look for the beginning of the file
  file.seekg(0, std::ios::beg);

 //create vector to hold all of the code
  std::vector<char> code(size);
 //read all of the data into the vector (like malloc())
  file.read(code.data(),code.size()); 

 //close the file 
  file.close();

  return code;

}

}//namespace shb