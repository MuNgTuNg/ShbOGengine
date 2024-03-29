#include <geometry/sMandelbrot.hpp>
namespace shb{


sShaderProgram sMandelbrot::m_ShaderProgram;
bool sMandelbrot::initOnce = false;

sMandelbrot::sMandelbrot(float x = 0.f, float y = 0.f, float z = 0.f) : sShape(x,y,z){

  if(!initOnce ){

    std::vector<sShader> shaders{ 
    {GL_FRAGMENT_SHADER, "mandelbrot.frag"},
    {GL_VERTEX_SHADER, "mandelbrot.vert"}
    };

    m_ShaderProgram = 
    {   
      "Mandelbrot shader program\n",                              
      shaders
    };

    ;

     //no longer need shaders
    for(int i = 0; i < shaders.size(); ++i){
      shaders[i].deleteShader();
    }

    //Has been initialised, static variables need not be initialised again
    initOnce = true;

    if(DEBUG_SHAPES){
      checkError(__FILE__,__LINE__,"Mandelbrot Constructor Texture initialisation:");
    }
  }



  // »»»»»»»»»»»»»»»»»»»»»»»» BUFFERS ««««««««««««««««««««««««««««««««««
  m_VertexBuffer.bindBuffer(GL_ARRAY_BUFFER);
  m_VertexBuffer.fillBuffer(m_Vertices, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);

  m_IndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);

  m_VAO.bind();
  m_VAO.format();
  


  //»»» CREATE INDEX BUFFER «««
  
  m_IndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);
  m_IndexBuffer.fillBuffer(m_Indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
 

  m_VertexBuffer.unBind(); //unbind so they cannot be modified after the fact 
  m_VAO.unBind();
  m_IndexBuffer.unBind();

  if(DEBUG_SHAPES){
      checkError(__FILE__,__LINE__,"Mandelbrot Constructor Buffers:");
  }
}

void sMandelbrot::getInput(){
    if(glfwGetKey(m_Window->handle(),GLFW_KEY_W) || glfwGetKey(m_Window->handle(),GLFW_KEY_SPACE)){
        offsetY += m_Camera->m_MoveSpeed;
    }
    if(glfwGetKey(m_Window->handle(),GLFW_KEY_A)){
        offsetX -= m_Camera->m_MoveSpeed;
    }
    if(glfwGetKey(m_Window->handle(),GLFW_KEY_S) || glfwGetKey(m_Window->handle(),GLFW_KEY_LEFT_SHIFT)){
        offsetY -= m_Camera->m_MoveSpeed;
    }
    if(glfwGetKey(m_Window->handle(),GLFW_KEY_D)){
        offsetX += m_Camera->m_MoveSpeed;
    }

    if(glfwGetKey(m_Window->handle(),GLFW_KEY_U)){
        m_Zoom -= m_Camera->m_MoveSpeed;
    }
     if(glfwGetKey(m_Window->handle(),GLFW_KEY_J)){
        m_Zoom += m_Camera->m_MoveSpeed;
    }
}

void sMandelbrot::update(sCamera& camera, double delta) {
    
   getInput();
  //»»»»»»»»»»»»»»»»»»»»»»»»»»»»»  UNIFORMS  ««««««««««««««««««««««««««««««««z
   
  //used as input data to the shader, can be modified at runtime
  m_ShaderProgram.useProgram();

  //»»»CAMERA RELATED «««
  //sends the "global" view off to the shader to affect all objects that use this shader program
  GLuint camMatrix = glGetUniformLocation(m_ShaderProgram.handle(),"cameraMatrix");
  glUniformMatrix4fv(camMatrix,1,GL_FALSE, glm::value_ptr(camera.m_CameraMatrix));

   
  //»»» OBJECT RELATED «««
  //sends off the "local" view of this particular object, essentially just it's location
  m_View = glm::translate( glm::mat4{1.f},glm::vec3(m_X,m_Y,m_Z));
  int view = glGetUniformLocation(m_ShaderProgram.handle(),"view");
  glUniformMatrix4fv(view,1,GL_FALSE,glm::value_ptr(m_View));

  //sends a rotation matrix off to the shader
  m_Rotation = glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(m_RotAxisx,m_RotAxisy,m_RotAxisz)); //TODO:: dedicate function to this
  GLuint rotation = glGetUniformLocation(m_ShaderProgram.handle(),"rotation");
  glUniformMatrix4fv(rotation, 1, GL_FALSE, glm::value_ptr(m_Rotation));

  //sends a scale variable off to the shader
  GLuint scale = glGetUniformLocation(m_ShaderProgram.handle(),"scale");       //use location to modify data from host side
  glUniform1f(scale, m_Scale);    
  
  GLuint offset = glGetUniformLocation(m_ShaderProgram.handle(),"offset");
  glUniform2f(offset, offsetX, offsetY );

  GLuint resolution = glGetUniformLocation(m_ShaderProgram.handle(),"resolution");
  glUniform2f(resolution, WINDOW_WIDTH, WINDOW_HEIGHT );
 
  GLuint zoom = glGetUniformLocation(m_ShaderProgram.handle(),"zoom");
  glUniform1f(zoom,  m_Zoom);
 


  //check if any functions failed to work
  if(DEBUG_SHAPES){
      checkError(__FILE__,__LINE__,"Mandelbrot Update:");
  }

 }


void sMandelbrot::draw(){
      //bind all things related to drawing
  m_IndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);//i want to draw from this index buffer in the next draw call
  m_VAO.bind();                                           //i want to use this format of vertices on the next draw call

  //draw currently bound index buffer
  glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] 
    
  //finished drawing these buffers so we want to unbind
  m_VertexBuffer.unBind();
  m_VAO.unBind();
   
}

void sMandelbrot::cleanup(){
    m_IndexBuffer.deleteBuffer();
    m_VertexBuffer.deleteBuffer();
    m_VAO.deleteVAO();
    m_ShaderProgram.deleteShaderProgram();

    if(DEBUG_SHAPES){
      checkError(__FILE__,__LINE__,"Pyramid Cleanup:");
    }
}


}//namespace shb