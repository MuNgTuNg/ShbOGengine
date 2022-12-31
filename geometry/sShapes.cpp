#include <sShapes.hpp>

namespace shb{

//static shaders so they don't have to be read over and over
sShader sPyramid::fragShader{};
sShader sPyramid::vertShader{};

//static program and textures to save time and space
sShaderProgram sPyramid::m_ShaderProgram{}; //shader program is a GPU executable

int sPyramid::m_TextureSlot = 0;
sTexture sPyramid::m_Texture{};

//boolean that only allows these to be initialised once
bool sPyramid::initOnce = false;





void sPyramid::init(){

 if(!initOnce ){

 //TODO:: add my cool AI generated logos to this engine
  m_TextureSlot = 0;
  m_Texture = {"makima","makima.jpeg", GL_TEXTURE_2D,GL_RGB, m_TextureSlot};

// »»» SHADERS «««
//  [TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]
  fragShader = {GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag"};
  vertShader = {GL_VERTEX_SHADER, "../shaders/vertex_shader.vert"};


// »»» SHADER PROGRAM «««  
 //shader program is an executable to be used on the gpu
 //Give it a name and initialise it. my name's jeff
  m_ShaderProgram = {"Pyramid shader\n"};
  m_ShaderProgram.init();

  //std::cout<<"\nvertShader Handle:: " << vertShader.handle() << "\n"; 
  //std::cout<<"fragShader Handle:: " << vertShader.handle() << "\n\n";

  m_ShaderProgram.addShader(vertShader.handle());
  m_ShaderProgram.addShader(fragShader.handle());
  checkError(__FILE__,__LINE__);

  m_ShaderProgram.linkProgram();
  checkError(__FILE__,__LINE__);
/*                   ^^^^^^^^^^^
ŋħŧħŋħŧħ←ŋˀħŋ←ĸ↓ŋ¢ĸˀ--PROBLEM AREA --»đŧˀħ”«ð“|ßeđ„|«ß“„ðß“
        SHADER HANDLES FAIL TO BE SENT AND 
        RECIEVED TO THE PROGRAM WITHOUT 
        THROWING AN ERROR FOR SOME REASON
ðæđ¶e←¶ŧ↓¶ſeøþŋſeþø„ſeŋþøẻđ”ſeþ→eſˀþđ→ſe”þđſ”eþđ”þſeø”þſ→e” 
*/
  fragShader.deleteShader(); //no longer need shaders
  vertShader.deleteShader();
   
  //»»» TEXTURES «««

  //Load the pixels from the image and load it into a texture in opengl
  m_Texture.loadTexture();

  //Send texture data off to the shader using the handle
  m_Texture.sendToShader(m_ShaderProgram.handle());

 //Has been initialised, static variables need not be initialised again
  initOnce = true;
   
 }

// »»»»»»»»»»»»»»»»»»»»»»»» BUFFERS ««««««««««««««««««««««««««««««««««

//»»» CREATES VERTEX BUFFER
  m_SquareVertexBuffer.init();
  m_SquareIndexBuffer.init();
  
  m_SquareVertexBuffer.bindBuffer(GL_ARRAY_BUFFER);
  m_SquareVertexBuffer.fillBuffer(m_Vertices, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);

  m_SquareIndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);

   
 //vertex attribute array (must have a currently bound vertex buffer to work properly)
 //VAO "Sucks up" the vertex buffer and associates the currently bound index buffer with
 //it
  
  m_VAO.bind();
  m_VAO.init();


//»»» CREATE INDEX BUFFER «««
  
  m_SquareIndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);
  m_SquareIndexBuffer.fillBuffer(m_Indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
 

  m_SquareVertexBuffer.unBind(); //unbind so they cannot be modified after the fact 
  m_VAO.unBind();
  m_SquareIndexBuffer.unBind();

  checkError(__FILE__,__LINE__);
}



void sPyramid::update(sCamera& camera, double delta ){

  // square update /////////////////////////////////
   //»»» LOCAL 3D «««

//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»  UNIFORMS  ««««««««««««««««««««««««««««««««z
   
   //used as input data to the shader, can be modified at runtime
    m_ShaderProgram.useProgram();

   //sends a scale variable off to the shader
    GLuint scaleUniform = glGetUniformLocation(m_ShaderProgram.handle(),"scale");       //use location to modify data from host side
    glUniform1f(scaleUniform, m_Scale);

   //sends a rotation matrix off to the shader
    m_Rotation = glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(m_RotAxisx,m_RotAxisy,m_RotAxisz));
    GLuint rotationMatrixUniform = glGetUniformLocation(m_ShaderProgram.handle(),"rotationMatrix");
    glUniformMatrix4fv(rotationMatrixUniform, 1, GL_FALSE, glm::value_ptr(m_Rotation));

   //sends the "global" view off to the shader to affect all objects that use this shader program
    GLuint viewUniform = glGetUniformLocation(sPyramid::m_ShaderProgram.handle(),"view");
    glUniformMatrix4fv(viewUniform,1,GL_FALSE,glm::value_ptr(camera.view));
    
   
   //sends off the "local" view of this particular object, essentially just it's location
    m_LocalView = glm::translate( glm::mat4{1.f},glm::vec3(m_X,m_Y,m_Z));
    int localViewUniform = glGetUniformLocation(m_ShaderProgram.handle(),"localView");
    glUniformMatrix4fv(localViewUniform,1,GL_FALSE,glm::value_ptr(m_LocalView));

   //the model matrix, pretty sure this is just 0,0
    int modelUniform = glGetUniformLocation(m_ShaderProgram.handle(),"model");
    glUniformMatrix4fv(modelUniform,1,GL_FALSE,glm::value_ptr(camera.model));

   // sends off the "global" projection matrix, which essentially is how i "see" the objects, perspective
    int projUniform = glGetUniformLocation(m_ShaderProgram.handle(),"proj");
    glUniformMatrix4fv(projUniform,1,GL_FALSE,glm::value_ptr(camera.proj));



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

    



   //bind all things related to drawing
    m_Texture.selectForUse();                                   //i want to draw this texture in the next draw 
    m_SquareIndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);//i want to draw from this index buffer in the next draw call
    m_VAO.bind();                                           //i want to use this format of vertices on the next draw call

   //draw currently bound index buffer
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] 
    

   //finished drawing these buffers so we want to unbind
    m_SquareVertexBuffer.unBind();
    m_VAO.unBind();
   
   //check if any functions failed to work
    checkError(__FILE__,__LINE__);

} 


void sPyramid::cleanup(){
  m_SquareIndexBuffer.deleteBuffer();
  m_SquareVertexBuffer.deleteBuffer();
  m_VAO.deleteVAO();
  m_ShaderProgram.deleteShaderProgram();
  m_Texture.deleteTexture();
  checkError(__FILE__,__LINE__);

}

}//namespace shb