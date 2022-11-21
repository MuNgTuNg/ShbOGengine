#include <sApp.hpp>
#include <glad.c>


namespace shb{



sApp::sApp(){}


void sApp::run(){


m_Window.initWindow();
m_Window.makeContextCurrent();

//glad is loaded on current context so it must be after window creation and 
//contextualisation
gladLoadGL();
  


// »»» SHADERS «««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]

  //fragShader
  sShader fragShader(GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag", true, true);

  //vertShader
  sShader vertShader(GL_VERTEX_SHADER, "../shaders/vertex_shader.vert", true,true);
  

// »»» SHADER PROGRAM «««
  m_ShaderProgram = glCreateProgram(); //creates a program object to which you can attach a shader object
  glAttachShader(m_ShaderProgram,vertShader.handle()); //specifies shader objects that will be linked to create a program
  glAttachShader(m_ShaderProgram,fragShader.handle()); //can check compatibility of shaders

  glLinkProgram(m_ShaderProgram);  //links program to create executables to run on processors (vertex, fragment, geometry)

  fragShader.deleteShader(); //no longer need shaders
  vertShader.deleteShader();




// »»» BUFFERS «««
  
  glGenVertexArrays(1,&m_VAO); //generate before vertex buffer (essentially manages vertex attributes)
  glGenBuffers(1, &m_VBO);               //inits buffer handles (can be array) »[num of buffers, pointer to buffers]

  glGenBuffers(1, &m_IBO);
  
  glBindVertexArray(m_VAO); 

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);  //specifies usage of buffer and allows handle to be used »[usage of buffer, buffer handle]
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW); //allocates and fills currently bound buffer and specifies usage [DYNAMIC,STATIC,STREAM][DRAW,READ,COPY]
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 3* sizeof(float), (void*)0); //tell opengl how we want to feed it to the shader we are using (how it's formatted)
  glEnableVertexAttribArray(0); //tell opengl to use slot 0 for the shader
  
  glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind so they cannot be modified after the fact 
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


// »»» RENDERING LOOP «««

//set the viewport            todo:: viewport does not draw whole screen in fullscreen mode
  glViewport(0,0,m_Window._height,m_Window._width);

  float r = 0;
  float g = 0;
  float b = 0;
  
  //»»» MAIN LOOP «««
  while (!glfwWindowShouldClose(m_Window._handle))
  {
    
    r += 0.001;
    g += 0.003;
    b += 0.004;
    
    if(r >= 1){
      r = 0;
    }
    if(g >= 1){
      g = 0;
    }
    if(b >= 1){
      b = 0;
    }
   
    glBindVertexArray(m_VAO);      //says that we want to feed the shader this specific way
    glUseProgram(m_ShaderProgram); //uses executable created earlier
    
    //set clear color
    
    glClearColor(r,g,b,1.f);
    
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW]
   
   //swap buffers
    glfwSwapBuffers(m_Window._handle); 

   
    
   
   //poll events
    glfwPollEvents();           //have any window events happened? 
  }
 

 
}


sApp::~sApp(){
     
 //cleanup
  glDeleteVertexArrays(1, & m_VAO);
  glDeleteBuffers(1,&m_VBO);
  glDeleteBuffers(1,&m_IBO);
  glDeleteProgram(m_ShaderProgram);
  m_Window.destroy();
  glfwTerminate();
}

}//namespace shb