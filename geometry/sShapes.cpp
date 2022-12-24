#include <sShapes.hpp>

namespace shb{

//static shaders so they don't have to be read over and over
sShader sPyramid::fragShader{};
sShader sPyramid::vertShader{};

//static program and textures to save time and space
sShaderProgram sPyramid::m_ShaderProgram1{}; //shader program is a GPU executable

int sPyramid::makimaTextureSlot = 0;
sTexture sPyramid::makimaTexture{};

//boolean that only allows these to be initialised once
bool sPyramid::initOnce = false;





void sPyramid::init(){

 if(!initOnce ){

 //TODO:: add my cool AI generated logos to this engine
  makimaTextureSlot = 0;
  makimaTexture = {"makima","icon2.jpeg", GL_TEXTURE_2D,GL_RGB, makimaTextureSlot};

// »»» SHADERS «««
//  [TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]
  fragShader = {GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag"};
  vertShader = {GL_VERTEX_SHADER, "../shaders/vertex_shader.vert"};


// »»» SHADER PROGRAM «««  
 //shader program is an executable to be used on the gpu
 //Give it a name and initialise it. my name's jeff
  m_ShaderProgram1 = {"Pyramid shader\n"};
  m_ShaderProgram1.init();

  //std::cout<<"\nvertShader Handle:: " << vertShader.handle() << "\n"; 
  //std::cout<<"fragShader Handle:: " << vertShader.handle() << "\n\n";

  m_ShaderProgram1.addShader(vertShader.handle());
  m_ShaderProgram1.addShader(fragShader.handle());
  checkError(__FILE__,__LINE__);

  m_ShaderProgram1.linkProgram();
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
  makimaTexture.loadTexture();

  //Send texture data off to the shader using the handle
  makimaTexture.sendToShader(m_ShaderProgram1.handle());

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



void sPyramid::update(glm::mat4 model, glm::mat4 view, glm::mat4 proj, double delta ){

  // square update /////////////////////////////////
   //»»» LOCAL 3D «««

//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»  UNIFORMS  ««««««««««««««««««««««««««««««««z

   //used as input data to the shader, can be modified at runtime
    m_ShaderProgram1.useProgram();

   //sends a scale variable off to the shader
    GLuint scaleUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"scale");       //use location to modify data from host side
    glUniform1f(scaleUniform, scale);

   //sends a rotation matrix off to the shader
    rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(rotAxisx,rotAxisy,rotAxisz));
    GLuint rotationMatrixUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"rotationMatrix");
    glUniformMatrix4fv(rotationMatrixUniform, 1, GL_FALSE, glm::value_ptr(rotation));

   //sends the "global" view off to the shader to affect all objects that use this shader program
    GLuint viewUniform = glGetUniformLocation(sPyramid::m_ShaderProgram1.handle(),"view");
    glUniformMatrix4fv(viewUniform,1,GL_FALSE,glm::value_ptr(view));

   //sends off the "local" view of this particular object, essentially just it's location
    glm::mat4 localView = glm::translate(view,glm::vec3(m_X,m_Y,m_Z));
    int localViewUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"localView");
    glUniformMatrix4fv(localViewUniform,1,GL_FALSE,glm::value_ptr(localView));

   //the model matrix, pretty sure this is just 0,0
    int modelUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"model");
    glUniformMatrix4fv(modelUniform,1,GL_FALSE,glm::value_ptr(model));

   // sends off the "global" projection matrix, which essentially is how i "see" the objects, perspective
    int projUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"proj");
    glUniformMatrix4fv(projUniform,1,GL_FALSE,glm::value_ptr(proj));



  //»»» UPDATES TO UNIFORM'S VALUES «««
  //object rotation angle modifications
    angle += 1.f * delta;
    if(angle >= 360.f){
      angle = 0.f;
    }
   
  //Object scale modifications
    float scaleSpeed = 0.5f;
    if(scale > 1.f){
      scalePeaked = true;
    }
    if(scalePeaked){
      if(scale <= 0.f){
        scalePeaked = false;
      }
      scale -= scaleSpeed * delta;
    }
    else if(scale <= 1.f){
      scale += scaleSpeed * delta;
    }

    



   //bind all things related to drawing
    makimaTexture.selectForUse();                                   //i want to draw this texture in the next draw 
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
  m_ShaderProgram1.deleteShaderProgram();
  makimaTexture.deleteTexture();
  checkError(__FILE__,__LINE__);

}

}//namespace shb