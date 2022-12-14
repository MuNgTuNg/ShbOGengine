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


//object that sholds the vertices
  
  sPyramid square;  //todo add vertex and index buffer objects to sShape class


//square.init();
// »»»»»»»»»»»»»»»»»»»»»»»»»»»»» SHADERS «««««««««««««««««««««««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]

  sShader fragShader(GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag");
  sShader vertShader(GL_VERTEX_SHADER, "../shaders/vertex_shader.vert");
  

// »»» SHADER PROGRAM «««  
  //shader program is an executable to be used on the gpu
  sShaderProgram m_ShaderProgram1{"Shader for textured square\n"};
   
  m_ShaderProgram1.addShader(fragShader);
  m_ShaderProgram1.addShader(vertShader);
  m_ShaderProgram1.linkProgram();

  fragShader.deleteShader(); //no longer need shaders
  vertShader.deleteShader();


  //»»» TEXTURES «««
  int makimaTextureSlot = 0;
  /*
  //create a texture 
  Params:
    1. Name in which it will be sent to the shader
    2. Name of file to be used
    3. Type of texture
    4. Format of texture
    5. Texture slot in which it will be used
  */
 //name of uniform doesnt seem to matter? todo
  sTexture makimaTexture("makima","makima.jpeg", GL_TEXTURE_2D,GL_RGB, makimaTextureSlot);

  //load the pixels from the image and load it into a texture in opengl
  makimaTexture.loadTexture();

  //send texture data off to the shader using the handle "makima"
  makimaTexture.sendToShader(m_ShaderProgram1.handle());




// »»»»»»»»»»»»»»»»»»»»»»»» BUFFERS ««««««««««««««««««««««««««««««««««

//»»» CREATES VERTEX BUFFER
 

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

  GLfloat angle = 0.1f;
  GLfloat rotAxisx = 0.1f;
  GLfloat rotAxisy = 0.1f;
  GLfloat rotAxisz = 0.1f;

  bool scalePeaked = false;

  //»»» 3D «««
  float x = 0.f;
  float y = 0.f;
  float z = -2.f;

  float fov = 45.f;



 
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  { 

   //»»» DELTA TIME «««
    m_CurrentFrameTime = glfwGetTime();       //get current time
    m_DeltaTime = m_CurrentFrameTime - m_PreviousFrameTime;//get amount of time elapsed since last frame
    m_PreviousFrameTime = m_CurrentFrameTime;               //set this frames time for next iteration comparison
    
    m_FrameTimeInSeconds = m_DeltaTime;
    m_FrameTimeInMS = m_DeltaTime *1000;

   

   //update window, keep viewport same size as screen
    m_Window.update();
   //init imgui
    tinkerWindow.startFrame();
    


   //»»» GLOBAL 3D «««
    glm::mat4 model = glm::mat4(1.f); 
    glm::mat4 view = glm::mat4(1.f); 
    glm::mat4 proj = glm::mat4(1.f); 

    view = glm::translate(view,glm::vec3(x,y,z));
    proj = glm::perspective(glm::radians(fov), (float)m_Window.width()/m_Window.height(),0.1f,100.f);
  

  // square update /////////////////////////////////
   //»»» LOCAL 3D «««
    int modelUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"model");
    int viewUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"view");
    int projUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"proj");
  
    glUniformMatrix4fv(modelUniform,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(viewUniform,1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(projUniform,1,GL_FALSE,glm::value_ptr(proj));



  //»»»ROTATION«««
   //runtime modifications
    angle += 1.f * m_FrameTimeInSeconds;
    if(angle >= 360.f){
      angle = 0.f;
    }
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(rotAxisx,rotAxisy,rotAxisz));
    
  //»»»SCALE«««
    float scaleSpeed = 0.5f;
    if(scale > 1.f){
      scalePeaked = true;
    }
    if(scalePeaked){
      if(scale <= 0.f){
        scalePeaked = false;
      }
      scale -= scaleSpeed * m_FrameTimeInSeconds;
    }
    else if(scale <= 1.f){
      scale += scaleSpeed * m_FrameTimeInSeconds;
    }

  //»»»COLOR«««
    //changing vertices color value by modifying buffer sent to shader

    // r += 0.001f * m_FrameTimeInSeconds;
    // g += 0.003f * m_FrameTimeInSeconds;
    // b += 0.004f * m_FrameTimeInSeconds;

    // if(r >= 1){
    //   r = 0;
      
    // }
    // if(g >= 1){
    //   g = 0;
    // }
    // if(b >= 1){
    //   b = 0;
    // }

    
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


   //bind all things related to drawing
    makimaTexture.bind();                                   //i want to draw this texture in the next draw 
    m_SquareIndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);//i want to draw from this index buffer in the next draw call
    m_VAO.bind();                                           //i want to use this format of vertices on the next draw call

   //draw currently bound index buffer
    glDrawElements(GL_TRIANGLES, square.indices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] 

   //finished drawing these buffers so we want to unbind
    m_SquareVertexBuffer.unBind();
    m_VAO.unBind();
   //////////////////////////////////////

   //imgui stuff
    //tinkerWindow could take an object as parameters instead of loads of variables
    tinkerWindow.update(scale,angle,x,y,z, fov , m_FrameTimeInMS, rotAxisx, rotAxisy, rotAxisz);
    tinkerWindow.render();

    //checkError(__FILE__,__LINE__);
   //swap buffers
    glfwSwapBuffers(m_Window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 

  //check for errors
  checkError(__FILE__,__LINE__);
   

  //shape.cleanup()
  m_SquareIndexBuffer.deleteBuffer();
  m_SquareVertexBuffer.deleteBuffer();
  m_VAO.deleteVAO();
  m_ShaderProgram1.deleteShaderProgram();
  makimaTexture.deleteTexture();

 
}


sApp::~sApp(){
     
 //cleanup
  tinkerWindow.destroyGUI();
  m_Window.destroy();
  glfwTerminate();
}

}//namespace shb