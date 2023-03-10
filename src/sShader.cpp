


#include <sShader.hpp>

namespace shb{

std::string sShader::readFile(const std::string & filePath) {
    std::string content;
    std::string FP = path + filePath;
    std::ifstream fileStream(FP, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist.\n" << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}


//»»» CREATION «««
sShader::sShader(GLenum type, const std::string& fp, bool compileOnCreation , bool setSourceOnCreation)
{
    m_Code = readFile(fp.c_str());         //save code read from file as member
    m_Source = m_Code.c_str();   //cast it to raw data

    m_Handle = glCreateShader(type);       //create handle //problem, 

    if(DEBUG_SHADERS){
      checkError(__FILE__,__LINE__,"Creating Shader Handle:");
    }

    if(setSourceOnCreation){
        setSource();
    }
    if(compileOnCreation){
        compile();
    }

    if(DEBUG){
      checkError(__FILE__,__LINE__,"Shader Constructor:");
    }
}


//»»» SOURCE CODE «««
void sShader::setSource(const char* source ){  //default value of source = shark
    if(strcmp(source,"shark") == 0){
        glShaderSource(m_Handle,1,&m_Source,NULL);               //associate source with handle (must be in same function call)
    }else{
        glShaderSource(m_Handle,1,&source,NULL);
    }

    if(DEBUG_SHADERS){
      checkError(__FILE__,__LINE__,"Setting Shader Source:");
    }
}




//»»» COMPILATION «««
void sShader::compile(){
    glCompileShader(m_Handle);

    

    GLint isCompiled = 0;
    glGetShaderiv(m_Handle, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
    	GLint maxLength = 0;
    	glGetShaderiv(m_Handle, GL_INFO_LOG_LENGTH, &maxLength);
    
    	// The maxLength includes the NULL character
    	std::vector<GLchar> errorLog(maxLength);
    	glGetShaderInfoLog(m_Handle, maxLength, &maxLength, &errorLog[0]);
    
    	// Provide the infolog in whatever manor you deem best.
    	// Exit with failure.
    	glDeleteShader(m_Handle); // Don't leak the shader.
    	return;
    }

    if(DEBUG_SHADERS){
      checkError(__FILE__,__LINE__,"Compiling Shader:");
    }
}


//»»» DELETION «««
void sShader::deleteShader(){
    glDeleteShader(m_Handle);
    m_Code.clear();
    m_Source = nullptr;

    if(DEBUG_SHADERS){
      checkError(__FILE__,__LINE__,"Delete shader:");
    }
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


//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
//»»»»»»»»»»»» sShaderProgram »»»»»»»»»»»»»»»»»»»»»»
//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»

//attach shader to program object (executable made for gpu)
void sShaderProgram::addShader(GLuint shader){
    glUseProgram(m_Handle);
    glAttachShader(m_Handle, shader); 

    if(DEBUG_SHADERS){
      checkError(__FILE__,__LINE__,"Adding Shader:");
    }
}


//initialises shader program and gives it a unique handle
 sShaderProgram::sShaderProgram(const char* name, std::vector<sShader> shaders) {

    //name the program
    m_ProgramName = name;
    GLuint handle = glCreateProgram();

    //check handle is valid
    if(DEBUG && handle == 0){
            std::cout << "Failed to create shader program\n";
    }

    m_Handle = handle;
    
    //attach all shaders passed in
    for(auto shader : shaders){
        glAttachShader(handle,shader.handle());
    } 
    

    glUseProgram(handle);  //FIX:: No idea what is going wrong
    
    if(DEBUG_SHADERS){
      checkError(__FILE__,__LINE__,"Using Shader Program:");
    }

    //link all shaders and shader programs to gpu executable 
    glLinkProgram(handle);     


    std::string log;
    GLint status; 
    glGetProgramiv( handle, GL_LINK_STATUS, &status ); 
    if( GL_FALSE == status ) {
        std::cerr << "Failed to link shader program!\n" << std::endl;
        GLint logLen; 
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLen); 
        if( logLen > 0 ) { 
            std::string(logLen, ' ');
            GLsizei written;
            glGetProgramInfoLog(handle, logLen, &written, &log[0]); 
            std::cerr << "Program log: " << std::endl << log;
        }
    }

    if(DEBUG_SHADERS){
      checkError(__FILE__,__LINE__,"Creating Shader Program:");
    }
}


void sShaderProgram::addShaders(std::vector<GLuint> shaders) { 
    for(auto shader : shaders){
        glAttachShader(m_Handle,shader);
    } 
} 


void sShaderProgram::useProgram(){
    glUseProgram(m_Handle);
}

void sShaderProgram::deleteShaderProgram(){
    glDeleteProgram(m_Handle);
}

}//namespace shb
