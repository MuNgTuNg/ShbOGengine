


#include "sShader.hpp"

namespace shb{

//»»» CREATION «««
sShader::sShader(int type, const std::string& fp, bool compileOnCreation, bool setSourceOnCreation)
{
    m_Handle = glCreateShader(type);       //create handle

    m_Code = createShaderSource(fp);         //save code read from file as member
    m_Source = reinterpret_cast<const char*>(m_Code.data());   //cast it to raw data

    if(setSourceOnCreation){
        setSource();
    }
    if(compileOnCreation){
        compile();
    }
        
}


//»»» SOURCE CODE «««
void sShader::setSource(const char* source ){  //default value of source = shark
    if(strcmp(source,"shark") == 0){
        glShaderSource(m_Handle,1,&m_Source,NULL);               //associate source with handle (must be in same function call)
    }else{
        glShaderSource(m_Handle,1,&source,NULL);
    }
}


std::vector<char> createShaderSource(const std::string& filePath){
 //open file at the end of the file (ate) in binary form, and open for input
  auto cwd = std::filesystem::current_path();
  
  std::ifstream file;
  file.open(filePath.c_str(), std::ios::ate |  std::ios::binary | std::ios::in );

 //check file is open
  if(!file.is_open()){
     std::string failed = "Failed to open file in: ";
     failed += cwd.c_str();
     DEBUGLOG(failed.c_str());
  }
  else{
     std::string success = "Successfully opened file in: ";
     success += cwd.c_str();
     DEBUGLOG(success.c_str());
  }

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

//»»» COMPILATION «««
void sShader::compile(){
    glCompileShader(m_Handle);
}


//»»» DELETION «««
void sShader::deleteShader(){
    glDeleteShader(m_Handle);
    m_Code.clear();
    m_Source = nullptr;
}


//»»» ERROR HANDLING «««
void sShader::handleErrors(){
         GLint isCompiled = 0;
         glGetShaderiv(m_Handle, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(m_Handle, GL_INFO_LOG_LENGTH, &maxLength);
         
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(m_Handle, maxLength, &maxLength, &errorLog[0]);
         
        for(GLchar word : errorLog){
            std::cout << word;
        }
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(m_Handle); // Don't leak the shader.
         	
    }
}





}//namespace shb
