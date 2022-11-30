#include <sApp.hpp>
#include <glad.c>


namespace shb{



sApp::sApp(){}


void sApp::run(){
//»»»WINDOW«««
  //creates window and initialises glad on current context by default
  m_Window.initWindow();



//»»» GUI «««
  m_GUI.initGUI();
 


// »»» SHADERS «««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]

  //fragShader
  sShader fragShader(GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag");

  //vertShader
  sShader vertShader(GL_VERTEX_SHADER, "../shaders/vertex_shader.vert");
  


// »»» SHADER PROGRAM «««  
  sShaderProgram shaderProgram1;
  shaderProgram1.addShader(fragShader);
  shaderProgram1.addShader(vertShader);
  shaderProgram1.linkProgram();

  fragShader.deleteShader(); //no longer need shaders
  vertShader.deleteShader();



// »»» BUFFERS «««
  sTriangle triangle; //object that holds the vertices
 
 //vertex attribute array
  glGenVertexArrays(1,&m_VAO); //generate before vertex buffer (essentially manages vertex attributes)
  glBindVertexArray(m_VAO); //"activate" the attrib array
 

 //inits buffer handles (can be array) »[num of buffers, pointer to buffers]
  glGenBuffers(1, &m_VBO);  //vertex buffer            

 //specifies usage of buffer and allows handle to be used »[usage of buffer, buffer handle]
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);  
  
//  //allocates and fills currently bound buffer and specifies usage [DYNAMIC,STATIC,STREAM][DRAW,READ,COPY]
  glBufferData(GL_ARRAY_BUFFER, triangle.vertices.size()*sizeof(GLfloat),&triangle.vertices[0], GL_DYNAMIC_DRAW); 

 //same again for index buffer
  glGenBuffers(1, &m_IBO);  //index buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle.indices.size() * sizeof(GLuint), &triangle.indices[0], GL_STATIC_DRAW);
  
  //position attribute
  //tell opengl how we want to feed it to the shader we are using (how it's formatted)
  glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 6* sizeof(float), (void*)0); //must be called after buffer being used is bound
  glEnableVertexAttribArray(0);                                              //tell opengl to use slot 0 for the shader
  
  //color attribute
  glVertexAttribPointer(1,3, GL_FLOAT,GL_FALSE, 6* sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1); 


  glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind so they cannot be modified after the fact 
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



//»»»UNIFORMS«««
   //used as input data to the shader, can be modified at runtime
  GLuint weirdColorOffset = glGetUniformLocation(shaderProgram1.handle(),"weirdColorOffset");  //find location within shader program
  GLuint scaleUniform = glGetUniformLocation(shaderProgram1.handle(),"scale");       //use location to modify data from host side
  GLuint rotationMatrixUniform =glGetUniformLocation(shaderProgram1.handle(),
                                     "rotationMatrix");




//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
//»»»»»»»»»»»»»»»»» MAIN LOOP STUFF »»»»»»»»»»»»»»»»»»»»»»»»»»»»
//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»

//»»»LOOP VARIABLES«««
  GLfloat r = 0.f;
  GLfloat g = 0.f;
  GLfloat b = 0.f;

  GLfloat scale = 1.f;
  GLfloat angle = 0.f;
  
  bool scalePeaked = false;
 
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  {
    
   //init imgui
    m_GUI.startFrame();
    

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

    triangle.vertices[3] = r +0.5f;
    triangle.vertices[4] = g +0.5f;
    triangle.vertices[5] = b +0.5f;

    triangle.vertices[9] = r +0.5f;
    triangle.vertices[10] = g +0.5f;
    triangle.vertices[11] = b +0.5f;

    triangle.vertices[15]  = r +0.5f;
    triangle.vertices[16]  = g +0.5f;
    triangle.vertices[17]  = b +0.5f;
    
    
    
   
    glUseProgram(shaderProgram1.handle()); //uses executable created earlier

    glUniform1f(weirdColorOffset, r);                         //send uniform data to selected locations and update them with current data at runtime
    glUniform1f(scaleUniform, scale);
    glUniformMatrix4fv(rotationMatrixUniform, 1, GL_FALSE, 
                      &rotationMatrix[0][0]);
   
   
   //update buffer at runtime
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, triangle.vertices.size()*sizeof(GLfloat),&triangle.vertices[0], GL_DYNAMIC_DRAW); 
    glBindBuffer(GL_ARRAY_BUFFER,0);
    
    glBindVertexArray(m_VAO);      //says that we want to feed the shader this specific way
                                   //holds the index buffer*



    
    //set clear color
    glClearColor(0.5f,0.f,0.f,1.f);
    glClear(GL_COLOR_BUFFER_BIT);



    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] //*which is why this works
   

   //imgui stuff
    m_GUI.beginWindow("Basic Window");
    ImGui::Text("Hello Hello Hello");
    ImGui::DragFloat("Rotation",&angle,0.01);
    ImGui::DragFloat("Scale",&scale,0.01);
    m_GUI.endWindow();


    m_GUI.render();

    m_Window.setViewPort();
   //swap buffers
    glfwSwapBuffers(m_Window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 

 
}


sApp::~sApp(){
     
 //cleanup
  m_GUI.destroyGUI();

  glDeleteVertexArrays(1, & m_VAO);
  glDeleteBuffers(1,&m_VBO);
  glDeleteBuffers(1,&m_IBO);

  glDeleteProgram(m_ShaderProgram);

  m_Window.destroy();

  glfwTerminate();
}

}//namespace shb