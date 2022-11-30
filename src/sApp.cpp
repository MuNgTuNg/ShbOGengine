#include <sApp.hpp>
#include <glad.c>


namespace shb{



sApp::sApp(){}


void sApp::run(){

//creates window and initialises glad on current context by default
  m_Window.initWindow();


// »»» SHADERS «««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]

  //fragShader
  sShader fragShader(GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag");

  //vertShader
  sShader vertShader(GL_VERTEX_SHADER, "../shaders/vertex_shader.vert");
  

// »»» SHADER PROGRAM ««« (object or no, i dont think it needs to be (yet at least))
  m_ShaderProgram = glCreateProgram(); //creates a program object to which you can attach a shader object
  glAttachShader(m_ShaderProgram,vertShader.handle()); //specifies shader objects that will be linked to create a program
  glAttachShader(m_ShaderProgram,fragShader.handle()); //can check compatibility of shaders

  glLinkProgram(m_ShaderProgram);  //links program to create executables to run on processors (vertex, fragment, geometry)

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
  GLuint colorUniform = glGetUniformLocation(m_ShaderProgram,"colorInput");  //find location within shader program
  GLuint scaleUniform = glGetUniformLocation(m_ShaderProgram,"scale");       //use location to modify data from host side
  GLuint rotationMatrixUniform =glGetUniformLocation(m_ShaderProgram,
                                     "rotationMatrix");



// »»» RENDERING LOOP «««


  GLfloat r = 0.f;
  GLfloat g = 0.f;
  GLfloat b = 0.f;

  GLfloat scale = 1.f;
  GLfloat angle = 0.f;
  
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(m_Window.handle(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
  
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window.handle()))
  {
    
   //init imgui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    
   //runtime modifications
    angle += .01f;
    r += 0.001f;
    g += 0.003f;
    b += 0.004f;

    scale += 0.001f;
    if(scale >= 2.f){
      scale = 0;
    }
    if(angle >= 360.f){
      angle = 0.f;
    }

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, 
                                  glm::vec3(0.0f,0.0f,1.0f));


  //changing vertices color value by modifying buffer sent to shader
    triangle.vertices[3] = r +0.5f;
    triangle.vertices[4] = g +0.5f;
    triangle.vertices[5] = b +0.5f;

    triangle.vertices[9] = r +0.5f;
    triangle.vertices[10] = g +0.5f;
    triangle.vertices[11] = b +0.5f;

    triangle.vertices[15]  = r +0.5f;
    triangle.vertices[16]  = g +0.5f;
    triangle.vertices[17]  = b +0.5f;
    
    
    if(r >= 1){
      r = 0;
      
    }
    if(g >= 1){
      g = 0;
    }
    if(b >= 1){
      b = 0;
    }
   
    glUseProgram(m_ShaderProgram); //uses executable created earlier

    glUniform1f(colorUniform, r);                         //send uniform data to selected locations and update them with current data at runtime
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
    ImGui::Begin("hello i am a window");
    ImGui::Text("hello chicken mena");


    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

   //swap buffers
    glfwSwapBuffers(m_Window.handle()); 
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 

 
}


sApp::~sApp(){
     
 //cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glDeleteVertexArrays(1, & m_VAO);
  glDeleteBuffers(1,&m_VBO);
  glDeleteBuffers(1,&m_IBO);
  glDeleteProgram(m_ShaderProgram);
  m_Window.destroy();
  glfwTerminate();
}

}//namespace shb