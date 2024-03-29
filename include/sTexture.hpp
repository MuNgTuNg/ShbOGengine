#pragma once

/*
                TODO:: 
                    Create map of textures and texture slots
*/

#include <string> 
#include <stb_image.h>
#include <sDebugging.hpp>

namespace shb{

class sTexture{
 public:
    sTexture(){}
      /*
  //create a texture 
  Params:
    1. Name in which it will be sent to the shader
    2. Name of file to be used
    3. Type of texture
    4. Format of texture
    5. Texture slot in which it will be used
  */
    sTexture(const char* texShaderName, const std::string& fileName, GLenum type, GLenum format){
        m_TexShaderName = texShaderName;
        m_Format = format;
        m_Type = type;
        m_Filename = fileName;
        m_TextureSlot = s_TextureSlot;
        ++s_TextureSlot;
        stbi_set_flip_vertically_on_load(true); //due to opengl
        glGenTextures(1,&m_TextureHandle);      //creates shader handle

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if(DEBUG_SHAPES){
            std::string msg = "Adding texture:" + fileName;
            checkError(__FILE__,__LINE__, msg );
        }
    }

    //selects this shader for use in the current context
    void selectForUse(){
        glActiveTexture(GL_TEXTURE0 + m_TextureSlot);
        
       
        if(DEBUG && !TURN_OFF_ANNOYING){
            checkError(__FILE__,__LINE__,"Selecting Texture:");
        }

        bind(); //use this one
        if(DEBUG && !TURN_OFF_ANNOYING){
            checkError(__FILE__,__LINE__,"Selecting Texture for use:");
        }
    }

   //sets state of texture 
    virtual void initParams(){ //todo add params to call
        selectForUse();
        unBind();
    }

    void sendToShader(GLuint shaderProgramHandle){
        GLuint texUniform = glGetUniformLocation(shaderProgramHandle, m_TexShaderName.c_str());
        glUseProgram(shaderProgramHandle);
        glUniform1i(texUniform,m_TextureSlot);

        if(DEBUG){
            checkError(__FILE__,__LINE__,"Sending Texture To Shader:");
        }
    }
   

    //the heavy operation, can be deferred
    void loadTexture(){
        selectForUse();
        loadPixels();
        if(m_Pixels == NULL){
          DEBUGLOG("failed to load texture pixels for: " + m_Filename);
        }

        //loads texture                                              //will not change*
        glTexImage2D(m_Type, 0, m_Format, m_Width,m_Height,0,m_Format, GL_UNSIGNED_BYTE,m_Pixels);     //*due to the library loading pixels as unsigned chars
        //generates mipmap
        glGenerateMipmap(m_Type);
        
        //frees the pixels, they have been loaded
        stbi_image_free(m_Pixels);
        unBind();

        if(DEBUG){
            checkError(__FILE__,__LINE__,"Loading Texture:");
        }
    }

    void deleteTexture(){
        glDeleteTextures(1,&m_TextureHandle);

        if(DEBUG){
            checkError(__FILE__,__LINE__,"Deleting Texture:");
        }
    }

  

    void bind(){
        glBindTexture(m_Type, m_TextureHandle);

        if(DEBUG){
            checkError(__FILE__,__LINE__,"Binding Texture:");
        }
    }
    void unBind(){
        glBindTexture(m_Type, 0);
    }

    void loadPixels(int desiredChannels = 0){
        m_Pixels = stbi_load((m_TexturePath + m_Filename).c_str(), &m_Width,&m_Height,&m_Channels,desiredChannels);
        if(m_Pixels == NULL){
          DEBUGLOG("failed to load texture pixels for: " + m_Filename);
        }
    }

  private:
    std::string m_TexturePath = "../resources/"; //path for all textures
    std::string m_Filename{}; //name of texture file
    std::string m_TexShaderName{}; //name of texture file

    int m_Height   = 0;   //height and width of image, and color channels (RGBA)
    int m_Width    = 0 ;
    int m_Channels = 0;

    GLuint m_TextureHandle = 0;
    GLenum m_Format = 0;
    GLenum m_Type = 0;
    static GLuint s_TextureSlot;
    GLuint m_TextureSlot = 0;

    GLuint m_ShaderProgramHandle = 0; //shader progrram to be used

    unsigned char* m_Pixels = NULL; //pointer to pixel data
};

} //namespace shb