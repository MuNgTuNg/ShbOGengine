#pragma once 
#include <geometry/sShapes.hpp>

namespace shb{

class sQuad : public sShape{
   public:
    
    
    sQuad (float x , float y , float z);
    void update(sCamera& camera, double delta) override;
    void draw() override;
    void cleanup() override;
    
   protected:
    std::vector<GLfloat> m_Vertices = 
    { //     COORDINATES     /        COLORS      /   TexCoord  //
      -1.f, -1.f,  0.f,  .9f,1.f,2.f,
      -1.f, 1.f,   0.f,  0.f,.5f,2.f,
      1.f,  1.f,    0.f,  2.f,1.f,.5f,
      1.f,  -1.f,   0.f,  2.f,.5f,2.f
    };
   
    std::vector<GLuint> m_Indices = 
    {
      0,1,2,
      0,2,3
    };


    vertColVAO m_VAO{};

    static sShaderProgram m_ShaderProgram;
    static bool initOnce;
};


class sFloor : public sQuad{
  public:
  sFloor(float x, float y, float z) : sQuad(x,y,z) {
   m_Y = z;
   m_Z = y;

   //start rotated by 90 degrees
   m_Model = glm::rotate(glm::mat4(1.f),glm::radians(-90.f), glm::vec3(1,0,0));
  }
  void update(sCamera& camera, double delta) override;
  
  
};





}//namespace shb