#pragma once 
#include <geometry/sShapes.hpp>

namespace shb{




class sIcosohedron : public sShape{
 public:
 
 sIcosohedron(float x, float y, float z);
 void update(sCamera& camera, double delta);//[TYPE OF SHADER, FILEPATH, COMPILE ON CREATION, SET SOURCE ON CREATION]
 void cleanup();

 void setScale(float scale){
    m_Scale = scale;
 }
 
 void rotate(){ //TODO 

 }

  std::vector<GLfloat> m_Vertices =
  { //     COORDINATES     /        COLORS      /   TexCoord  //
    0.000f,    0.000f,    1.000f,   1.f,1.f,1.f,   0.0f,1.f,
    0.894f,    0.000f,    0.447f,   1.f,1.f,1.f,  -0.5f,5.f,
    0.276f,    0.851f,    0.447f,   1.f,1.f,1.f,   0.5f,0.f,
   -0.724f,    0.526f,    0.447f,   1.f,1.f,1.f,  -0.5f,5.f,
   -0.724f,   -0.526f,    0.447f,   1.f,1.f,1.f,   0.5f,0.f,
    0.276f,   -0.851f,    0.447f,   1.f,1.f,1.f,  -0.5f,5.f,
    0.724f,    0.526f,   -0.447f,   1.f,1.f,1.f,   0.5f,0.f,
   -0.276f,    0.851f,   -0.447f,   1.f,1.f,1.f,  -0.5f,5.f,
   -0.894f,    0.000f,   -0.447f,   1.f,1.f,1.f,   0.5f,0.f,
   -0.276f,   -0.851f,   -0.447f,   1.f,1.f,1.f,  -0.5f,5.f,
    0.724f,   -0.526f,   -0.447f,   1.f,1.f,1.f,   0.5f,0.f,
    0.000f,    0.000f,   -1.000f,   1.f,1.f,1.f,   0.5f,0.f,
  };

  std::vector<GLuint> m_Indices =
  {
    2,   1,   0,
    3,   2,   0,
    4,   3,   0,
    5,   4,   0,
    1,   5,   0,
    11,  6,   7,
    11,  7,   8,
    11,  8,   9,
    11,  9,   10,
    11,  10,  6,
    1,   2,   6,
    2,   3,   7,
    3,   4,   8,
    4,   5,   9,
    5,   1,   10,
    2,   7,   6,
    3,   8,   7,
    4,   9,   8,
    5,   10,  9,
    1,   6,   10 
  };

  static sShader fragShader;
  static sShader vertShader;
  static sShaderProgram m_ShaderProgram;
  static int m_TextureSlot;
  static sTexture m_Texture;


  GLfloat m_Scale = 1.f;
  float m_ScaleSpeed = 0.f;
  bool m_ScalePeaked = false;
  float m_ScalePeak = 50.f;


  glm::mat4 m_Rotation{};

  GLfloat m_Angle = 0.1f;
  GLfloat m_RotAxisx = 0.1f;
  GLfloat m_RotAxisy = 0.1f;
  GLfloat m_RotAxisz = 0.1f;


  static bool initOnce;

};


}//namespace shb