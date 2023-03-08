


#include <sShader.hpp>

namespace shb{

std::string sShader::readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
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
    checkError(__FILE__,__LINE__);

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




//»»» COMPILATION «««
void sShader::compile(){
    glCompileShader(m_Handle);
    //checkError(__FILE__,__LINE__);
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


//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
//»»»»»»»»»»»» sShaderProgram »»»»»»»»»»»»»»»»»»»»»»
//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»

//attach shader to program object (executable made for gpu)
void sShaderProgram::addShader(GLuint shader){
    useProgram();
    glAttachShader(m_Handle, shader); //problem area (this handle is being corrupted or something)
    //std::cout << "shaderProgramHandle: " << m_Handle << "\nshader handle: " << shader.handle() << "\n"  ;
    //checkError(__FILE__,__LINE__);
}

//link all shaders and shader programs to gpu executable 
void sShaderProgram::linkProgram(){
    useProgram();
    glLinkProgram(m_Handle);      //problem area (this handle is being corrupted or something)
    //checkError(__FILE__,__LINE__);


    std::string log;
    GLint status; 
    glGetProgramiv( m_Handle, GL_LINK_STATUS, &status ); 
    if( GL_FALSE == status ) {
        std::cerr << "Failed to link shader program!" << std::endl;
        GLint logLen; 
        glGetProgramiv(m_Handle, GL_INFO_LOG_LENGTH, &logLen); 
        if( logLen > 0 ) { 
            std::string(logLen, ' ');
            GLsizei written;
            glGetProgramInfoLog(m_Handle, logLen, &written, &log[0]); 
            std::cerr << "Program log: " << std::endl << log;
        }
    }
}


//initialises shader program and gives it a unique handle
sShaderProgram::sShaderProgram(const char* name) {
    m_ProgramName = name;
    m_Handle = glCreateProgram();
     if(m_Handle == 0){
        DEBUGLOG("Failed to create shader program");
    }else{
        // std::string res = "created shader programme";
        // DEBUGLOG(res.c_str());
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
