#include <sApp.hpp>
#include <glad.c>
#include <stb_image.h>


namespace shb{





sApp::sApp(){}


void sApp::run(){
//»»»WINDOW«««
  //creates window and initialises glad on current context by default
  m_Window.initWindow();

//»»» GUI «««
  tinkerWindow.initGUI();



// »»»»»»»»»»»»»»»»»»»»»»»»»»»»» SHADERS «««««««««««««««««««««««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]

  //fragShader
  sShader fragShader(GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag");

  //vertShader
  sShader vertShader(GL_VERTEX_SHADER, "../shaders/vertex_shader.vert");
  


// »»» SHADER PROGRAM «««  
  //shader program is an executable to be used on the gpu
  sShaderProgram m_ShaderProgram1{};
   
  m_ShaderProgram1.addShader(fragShader);
  m_ShaderProgram1.addShader(vertShader);
  m_ShaderProgram1.linkProgram();

  fragShader.deleteShader(); //no longer need shaders
  vertShader.deleteShader();




//øøøøøøøøøøøøøøøøøøøøøøøøøø todo create texture class

//»»» TEXTURES «««
std::string texturePath = "../resources/";
std::string makimaTexture = "makima.png";
int makHeight, makWidth, makChannels;
stbi_set_flip_vertically_on_load(true);
unsigned char* pixels = stbi_load((texturePath + makimaTexture).c_str(),&makWidth,&makHeight,&makChannels,0);
  
GLuint texture;
glGenTextures(1,&texture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//loads texture
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, makWidth,makHeight,0,GL_RGBA, GL_UNSIGNED_BYTE,pixels);
//generates mipmap
glGenerateMipmap(GL_TEXTURE_2D);

//frees the pixels, they have been loaded
stbi_image_free(pixels);
glBindTexture(GL_TEXTURE_2D, 0);

GLuint tex0Uniform = glGetUniformLocation(m_ShaderProgram1.handle(), "tex0");

//uses executable created earlier
m_ShaderProgram1.useProgram();
glUniform1i(tex0Uniform,0);



//øøøøøøøøøøøøøøøøøøøøø




// »»»»»»»»»»»»»»»»»»»»»»»» BUFFERS ««««««««««««««««««««««««««««««««««

//»»» CREATES VERTEX BUFFER
 //object that holds the vertices
  sSquare square;  //todo add vertex and index buffer objects to sShape class

//»»» CREATES VERTEX INPUT DATA ««« (create a vertex class and use offsetof() and sizeof())


  BufferObject m_SquareVertexBuffer{}; 
  m_SquareVertexBuffer.bindBuffer(GL_ARRAY_BUFFER);
  m_SquareVertexBuffer.fillBuffer(square.vertices, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);


 //vertex attribute array (must have a currently bound vertex buffer to work properly)
 //VAO "Sucks up" the vertex buffer and associates the currently bound index buffer with
 //it
  defaultVAO m_VAO{};
  m_VAO.bind();
  m_VAO.init();


//»»» CREATE INDEX BUFFER «««
  BufferObject m_SquareIndexBuffer{};
  m_SquareIndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);
  m_SquareIndexBuffer.fillBuffer(square.indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
  
 

  m_SquareVertexBuffer.unBind(); //unbind so they cannot be modified after the fact 
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»  UNIFORMS  ««««««««««««««««««««««««««««««««z
   //used as input data to the shader, can be modified at runtime
  GLuint weirdColorOffset = glGetUniformLocation(m_ShaderProgram1.handle(),"weirdColorOffset");  //find location within shader program
  GLuint scaleUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"scale");       //use location to modify data from host side
  GLuint rotationMatrixUniform =glGetUniformLocation(m_ShaderProgram1.handle(),
                                     "rotationMatrix");



//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
//»»»»»»»»»»»»»»»»» MAIN LOOP STUFF »»»»»»»»»»»»»»»»»»»»»»»»»»»»
//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»

//»»»SQUARE VARIABLES«««
  GLfloat r = 0.f;
  GLfloat g = 0.f;
  GLfloat b = 0.f;

  GLfloat scale = 1.f;
  GLfloat angle = 0.f;
  
  bool scalePeaked = false;

 

  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  { 
   //update window, keep viewport same size as screen
    m_Window.update();
   //init imgui
    tinkerWindow.startFrame();
    




  //»»»ROTATION«««
   //runtime modifications
    angle += .01f;
    if(angle >= 360.f){
      angle = 0.f;
    }
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, 
                                  glm::vec3(0.0f,0.0f,1.0f));

  //»»»SCALE«««
    if(scale > 2.f){
      scalePeaked = true;
    }
    if(scalePeaked){
      if(scale <= 0.f){
        scalePeaked = false;
      }
      scale -= 0.001f;
    }
    else if(scale <= 2.f){
      scale += 0.001f;
    }

  //»»»COLOR«««
    //changing vertices color value by modifying buffer sent to shader

    r += 0.001f;
    g += 0.003f;
    b += 0.004f;

    if(r >= 1){
      r = 0;
      
    }
    if(g >= 1){
      g = 0;
    }
    if(b >= 1){
      b = 0;
    }

    
   //uses executable created earlier to push uniforms into it to be fed to the shaders
    m_ShaderProgram1.useProgram();
    glUniform1f(weirdColorOffset, r);                         //send uniform data to selected locations and update them with current data at runtime
    glUniform1f(scaleUniform, scale);
    glUniformMatrix4fv(rotationMatrixUniform, 1, GL_FALSE, &rotationMatrix[0][0]);
    

   //update buffer at runtime
    //shape.updateVertexBuffer()
    m_SquareVertexBuffer.bindBuffer(GL_ARRAY_BUFFER);
    m_SquareVertexBuffer.fillBuffer(square.vertices,GL_ARRAY_BUFFER,GL_DYNAMIC_DRAW);
    m_SquareVertexBuffer.unBind();

    
   //i want to draw this texture in the next draw call
    //shape.bindTexture();
    glBindTexture(GL_TEXTURE_2D, texture);
   //i want to draw from this index buffer in the next draw call
    m_SquareIndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);
   //i want to use this format of vertices on the next draw call
    //shape.bindVAO();
    m_VAO.bind();      
   //draw currently bound index buffer
    glDrawElements(GL_TRIANGLES, square.indices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] //*which is why this works
   //////////////////////////////////////

   //imgui stuff
    tinkerWindow.update(scale,angle);
    tinkerWindow.render();

    //checkError(__FILE__,__LINE__);
   //swap buffers
    glfwSwapBuffers(m_Window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 

  m_VAO.deleteVAO();

  //check for errors
  checkError(__FILE__,__LINE__);
   

  //shape.cleanup()
  m_SquareIndexBuffer.deleteBuffer();
  m_SquareVertexBuffer.deleteBuffer();
  m_ShaderProgram1.deleteShaderProgram();
  glDeleteTextures(1,&texture);

 
}


sApp::~sApp(){
     
 //cleanup
  tinkerWindow.destroyGUI();
  m_Window.destroy();
  glfwTerminate();
}

}//namespace shb