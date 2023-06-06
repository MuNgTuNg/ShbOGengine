#include <geometry/sIcosohedron.hpp>



namespace shb{



/*  
          Static variables
            Textures, shaders, bools to check initialisation of textures
*/
sShaderProgram sIcosohedron::m_ShaderProgram; 

sTexture sIcosohedron::m_Texture{};
bool sIcosohedron::initOnce = false;


sIcosohedron::sIcosohedron(float x = 0.f, float y = 0.f, float z = 0.f) : sShape(x,y,z) {
  m_Name = "Icosohedron";

  if(!initOnce ){

    m_Texture = {"makima","makimaa.jpeg", GL_TEXTURE_2D,GL_RGB};


    std::vector<sShader> shaders{ 
    {GL_FRAGMENT_SHADER, "icosohedron_shader.frag"},
    {GL_VERTEX_SHADER, "icosohedron_shader.vert"}
    };

    m_ShaderProgram = 
    {   
      "Icosohedron shader program\n",                              
      shaders
    };

    ;

     //no longer need shaders
    for(int i = 0; i < shaders.size(); ++i){
      shaders[i].deleteShader();
    }

    //Load the pixels from the image and load it into a texture in opengl
    m_Texture.loadTexture();

    //Send texture data off to the shader using the handle
    m_Texture.sendToShader(m_ShaderProgram.handle());

    //Has been initialised, static variables need not be initialised again
    initOnce = true;

    if(DEBUG_SHAPES){
      checkError(__FILE__,__LINE__,"Icosohedron Constructor Texture initialisation:");
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
      checkError(__FILE__,__LINE__,"Icosohedron Constructor Buffers:");
  }
}



void sIcosohedron::update(sCamera& camera, double delta ){


 //»»» UPDATES TO UNIFORM'S VALUES «««
  //object rotation angle modifications
  m_Angle += 1.f * delta;
  if(m_Angle >= 360.f){
    m_Angle = 0.f;
  }
   
  //Object scale modifications
    
  if(m_Scale > m_ScalePeak){
    m_ScalePeaked = true;
  }
  if(m_ScalePeaked){
    if(m_Scale <= 0.f){
      m_ScalePeaked = false;
    }
    m_Scale -= m_ScaleSpeed * delta;
  }
  else if(m_Scale <= m_ScalePeak){
    m_Scale += m_ScaleSpeed * delta;
  }


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
  int localViewUniform = glGetUniformLocation(m_ShaderProgram.handle(),"view");
  glUniformMatrix4fv(localViewUniform,1,GL_FALSE,glm::value_ptr(m_View));

  //sends a rotation matrix off to the shader
  m_Rotation = glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(m_RotAxisx,m_RotAxisy,m_RotAxisz)); //TODO:: dedicate function to this
  GLuint localRotationMatrix = glGetUniformLocation(m_ShaderProgram.handle(),"localRotationMatrix");
  glUniformMatrix4fv(localRotationMatrix, 1, GL_FALSE, glm::value_ptr(m_Rotation));

  //sends a scale variable off to the shader
  GLuint scaleUniform = glGetUniformLocation(m_ShaderProgram.handle(),"scale");       //use location to modify data from host side
  glUniform1f(scaleUniform, m_Scale);    


  //check if any functions failed to work
  if(DEBUG_SHAPES){
      checkError(__FILE__,__LINE__,"Icosohedron Update:");
  }

} 

void sIcosohedron::draw(){

  //bind all things related to drawing
  m_Texture.selectForUse();                                   //i want to draw this texture in the next draw 
  m_IndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);//i want to draw from this index buffer in the next draw call
  m_VAO.bind();                                           //i want to use this format of vertices on the next draw call

  //draw currently bound index buffer
  glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] 
    
  //finished drawing these buffers so we want to unbind
  m_VertexBuffer.unBind();
  m_VAO.unBind();
   
}


void sIcosohedron::cleanup(){
  m_IndexBuffer.deleteBuffer();
  m_VertexBuffer.deleteBuffer();
  m_VAO.deleteVAO();
  m_ShaderProgram.deleteShaderProgram();
  m_Texture.deleteTexture();

  if(DEBUG_SHAPES){
      checkError(__FILE__,__LINE__,"Icosohedron Destructor:");
  }
}

}//namespace shb