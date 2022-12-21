#pragma once

//////
/*
øøøøøøøøøøøøøøøøøøøøøøøøøøøøøøø member variables
»»» texture path                          ✓
»»» name of individual texture            ✓
»»» height width and channels of texture  ✓
»»» GLenum slot of texture
»»» handle to shader program

»»» target (GL_TEXTURE_2D)
»»» mipmap level ?
»»» format (GL_RGBA)
»»» type; how the data is stored (GL_UNSIGNED_BYTE, GL_INT) 

øøøøøøøøøøøøøøøøøøøøøøøøøøøøø texture lifetime
»»» load pixels in to unsigned char                     [stbi_load]
»»» check pixels != NULL                                
»»» generate textures                                   [glGenTextures]
»»» activate texture at texture slot (GL_TEXTURE0) etc  [glActiveTexture]
»»» bind texture to be used                             [glBindTexture(GL_TEXTURE_2D, textureHandle)]
»»» set texture parameters                              [glTexParameter]
»»» load texture                                        [glTexImage2D]
»»» generate mipmaps                                    [glGenerateMipMap]
»»» free pixels                                         [stbi_image_free]
»»» unbind texture                                      [glBindTexture]
»»»
»»» create uniform variable                             [glGetUniformLocation(shaderProgHandle, nameOfuniformLocation)]
»»» use shader program                                  [glUseProgram]
»»» send off uniform                                    [glUniform*()]

øøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøøø usage
»»» bind texture in update function of game object      [glBindTexture]

*/
#include <string> 
#include <stb_image.h>
#include <sUtils.hpp>

namespace shb{

class sTexture{
 public:
    sTexture(){
        
    }
    sTexture(const char* texShaderName, const char* fileName, GLenum type, GLenum format, int textureSlot){
        m_TexShaderName = texShaderName;
        m_Format = format;
        m_Type = type;
        m_TextureSlot = textureSlot;
        m_Filename = fileName;
        stbi_set_flip_vertically_on_load(true); //due to opengl
        glGenTextures(1,&m_TextureHandle);      //creates shader handle
    }

    //selects this shader for use in the current context
    void selectForUse(){
        selectTexture(); //choose to use selected texture slot 
        bind(); //use this one
    }

   //sets state of texture 
    virtual void initParams(){ //todo add params to call
        selectForUse();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        unBind();
    }

    void sendToShader(GLuint shaderProgramHandle){
        GLuint texUniform = glGetUniformLocation(shaderProgramHandle, m_TexShaderName.c_str());
        glUseProgram(shaderProgramHandle);
        glUniform1i(texUniform,m_TextureSlot);
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
    }

    virtual void update(){
      

    }

    void deleteTexture(){
        glDeleteTextures(1,&m_TextureHandle);
    }

    void selectTexture(){
        glActiveTexture(GL_TEXTURE0 + m_TextureSlot);
    }

    void bind(){
        glBindTexture(m_Type, m_TextureHandle);
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
    const std::string m_TexturePath = "../resources/"; //path for all textures
    std::string m_Filename{}; //name of texture file
    std::string m_TexShaderName{}; //name of texture file

    int m_Height   = 0;   //height and width of image, and color channels (RGBA)
    int m_Width    = 0 ;
    int m_Channels = 0;

    GLuint m_TextureHandle;
    GLenum m_Format;
    GLenum m_Type;
    int m_TextureSlot = 0;

    GLuint m_ShaderProgramHandle; //shader progrram to be used

    unsigned char* m_Pixels = NULL; //pointer to pixel data
};

} //namespace shb