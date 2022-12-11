//////
/*
øøøøøøøøøøøøøøøøøøøøøøøøøøøøøøø member variables
»»» texture path
»»» name of individual texture
»»» height width and channels of texture
»»» GLenum slot of texture
»»» handle to shader program

øøøøøøøøøøøøøøøøøøøøøøøøøøøøø texture lifetime
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