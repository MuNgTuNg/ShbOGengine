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
  m_GUI.initGUI();
 


// »»»»»»»»»»»»»»»»»»»»»»»»»»»»» SHADERS «««««««««««««««««««««««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]

  //fragShader
  sShader fragShader(GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag");

  //vertShader
  sShader vertShader(GL_VERTEX_SHADER, "../shaders/vertex_shader.vert");
  


// »»» SHADER PROGRAM «««  
  //shader program is an executable to be used on the gpu
  sShaderProgram shaderProgram1;
  shaderProgram1.addShader(fragShader);
  shaderProgram1.addShader(vertShader);
  shaderProgram1.linkProgram();

  fragShader.deleteShader(); //no longer need shaders
  vertShader.deleteShader();


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

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, makWidth,makHeight,0,GL_RGBA, GL_UNSIGNED_BYTE,pixels);
glGenerateMipmap(GL_TEXTURE_2D);

stbi_image_free(pixels);
glBindTexture(GL_TEXTURE_2D, 0);

GLuint tex0Uniform = glGetUniformLocation(shaderProgram1.handle(), "tex0");

//uses executable created earlier
shaderProgram1.useProgram();
glUniform1i(tex0Uniform,0);
   

// »»»»»»»»»»»»»»»»»»»»»»»» BUFFERS ««««««««««««««««««««««««««««««««««

//»»» CREATES VERTEX BUFFER
 //object that holds the vertices
  sSquare shape; 
 //inits buffer handles (can be array) »[num of buffers, pointer to buffers]
  glGenBuffers(1, &m_VBO);  //vertex buffer            
 //specifies usage of buffer and allows handle to be used »[usage of buffer, buffer handle]
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);  
//  //allocates and fills currently bound buffer and specifies usage [DYNAMIC,STATIC,STREAM][DRAW,READ,COPY]
  glBufferData(GL_ARRAY_BUFFER, shape.vertices.size()*sizeof(GLfloat),&shape.vertices[0], GL_DYNAMIC_DRAW); 

 
//»»» CREATES VERTEX INPUT DATA ««« (create a vertex class and use offsetof() and sizeof())
 //vertex attribute array
  glGenVertexArrays(1,&m_VAO); //generate before vertex buffer (essentially manages vertex attributes)
  glBindVertexArray(m_VAO); //"activate" the attrib array
 
  //position attribute
  //tell opengl how we want to feed it to the shader we are using (how it's formatted)
  glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 8* sizeof(float), (void*)0); //must be called after buffer being used is bound
  glEnableVertexAttribArray(0);                                              //tell opengl to use slot 0 for the shader
  
  //color attribute
  glVertexAttribPointer(1,3, GL_FLOAT,GL_FALSE, 8* sizeof(float), (void*)(3*sizeof(float)));
  glEnableVertexAttribArray(1); 

 //texture attribute
  glVertexAttribPointer(2,2, GL_FLOAT,GL_FALSE, 8* sizeof(float), (void*)(6*sizeof(float)));
  glEnableVertexAttribArray(2); 


//»»» CREATE INDEX BUFFER «««
  glGenBuffers(1, &m_IBO);  //index buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indices.size() * sizeof(GLuint), &shape.indices[0], GL_STATIC_DRAW);
  
 

  glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind so they cannot be modified after the fact 
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»  UNIFORMS  ««««««««««««««««««««««««««««««««z
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

  //use this vertex array for the whole loop every time
  glBindVertexArray(m_VAO);      //says that we want to feed the shader this specific way
                                   //Vertex Arrays USE THE LAST ELEMENT_ARRAY_BUFFER THAT WAS BOUND 
 
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

    // triangle.vertices[3] = r +0.5f;
    // triangle.vertices[4] = g +0.5f;
    // triangle.vertices[5] = b +0.5f;

    // triangle.vertices[9] = r +0.5f;
    // triangle.vertices[10] = g +0.5f;
    // triangle.vertices[11] = b +0.5f;

    // triangle.vertices[15]  = r +0.5f;
    // triangle.vertices[16]  = g +0.5f;
    // triangle.vertices[17]  = b +0.5f;
    
    
      //uses executable created earlier
    shaderProgram1.useProgram();
   

    glUniform1f(weirdColorOffset, r);                         //send uniform data to selected locations and update them with current data at runtime
    glUniform1f(scaleUniform, scale);
    glUniformMatrix4fv(rotationMatrixUniform, 1, GL_FALSE, &rotationMatrix[0][0]);
    

    glBindTexture(GL_TEXTURE_2D, texture);
   
   //update buffer at runtime
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, shape.vertices.size()*sizeof(GLfloat),&shape.vertices[0], GL_DYNAMIC_DRAW); 
    glBindBuffer(GL_ARRAY_BUFFER,0);

    //set clear color
    glClearColor(0.5f,0.f,0.f,1.f);
    glClear(GL_COLOR_BUFFER_BIT);



    glDrawElements(GL_TRIANGLES, shape.indices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] //*which is why this works
   

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