#include <sShapes.hpp>

namespace shb{

void sPyramid::init(){
    // »»»»»»»»»»»»»»»»»»»»»»»»»»»»» SHADERS «««««««««««««««««««««««
//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]
   
  fragShader = {GL_FRAGMENT_SHADER, "../shaders/fragment_shader.frag"};
  vertShader = {GL_VERTEX_SHADER, "../shaders/vertex_shader.vert"};
  
   
// »»» SHADER PROGRAM «««  
  //shader program is an executable to be used on the gpu
  m_ShaderProgram1 = {"Shader for textured square\n"};
   
  m_ShaderProgram1.addShader(fragShader);
  m_ShaderProgram1.addShader(vertShader);
  m_ShaderProgram1.linkProgram();

  fragShader.deleteShader(); //no longer need shaders
  vertShader.deleteShader();

   
  //»»» TEXTURES «««

  //load the pixels from the image and load it into a texture in opengl
  makimaTexture.loadTexture();

  //send texture data off to the shader using the handle "makima"
  makimaTexture.sendToShader(m_ShaderProgram1.handle());

   


// »»»»»»»»»»»»»»»»»»»»»»»» BUFFERS ««««««««««««««««««««««««««««««««««

//»»» CREATES VERTEX BUFFER
  m_SquareVertexBuffer.init();
  m_SquareIndexBuffer.init();
  
  m_SquareVertexBuffer.bindBuffer(GL_ARRAY_BUFFER);
  m_SquareVertexBuffer.fillBuffer(m_Vertices, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);

   
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



//»»»»»»»»»»»»»»»»»»»»»»»»»»»»»  UNIFORMS  ««««««««««««««««««««««««««««««««z
   //used as input data to the shader, can be modified at runtime
  weirdColorOffset = glGetUniformLocation(m_ShaderProgram1.handle(),"weirdColorOffset");  //find location within shader program
  scaleUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"scale");       //use location to modify data from host side
  rotationMatrixUniform = glGetUniformLocation(m_ShaderProgram1.handle(),"rotationMatrix");


}



void sPyramid::update(glm::mat4 model, glm::mat4 view, glm::mat4 proj, double delta ){

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
    angle += 1.f * delta;
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
      scale -= scaleSpeed * delta;
    }
    else if(scale <= 1.f){
      scale += scaleSpeed * delta;
    }

  //»»»COLOR«««
    //changing vertices color value by modifying buffer sent to shader

    // r += 0.001f * delta;
    // g += 0.003f * delta;
    // b += 0.004f * delta;

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
    m_SquareVertexBuffer.fillBuffer(m_Vertices,GL_ARRAY_BUFFER,GL_DYNAMIC_DRAW);
    m_SquareVertexBuffer.unBind();


   //bind all things related to drawing
    makimaTexture.bind();                                   //i want to draw this texture in the next draw 
    m_SquareIndexBuffer.bindBuffer(GL_ELEMENT_ARRAY_BUFFER);//i want to draw from this index buffer in the next draw call
    m_VAO.bind();                                           //i want to use this format of vertices on the next draw call

   //draw currently bound index buffer
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT , 0); //[PRIMITIVE, OFFSET, NUMBER TO DRAW] 

   //finished drawing these buffers so we want to unbind
    m_SquareVertexBuffer.unBind();
    m_VAO.unBind();
   //////////////////////////////////////
} 


void sPyramid::cleanup(){
  m_SquareIndexBuffer.deleteBuffer();
  m_SquareVertexBuffer.deleteBuffer();
  m_VAO.deleteVAO();
  m_ShaderProgram1.deleteShaderProgram();
  makimaTexture.deleteTexture();

}

}//namespace shb