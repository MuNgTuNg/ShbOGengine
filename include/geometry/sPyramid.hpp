#pragma once

#include <geometry/sShapes.hpp>

namespace shb{
class sPyramid : public sShape{
 public:
 
 
 sPyramid(float x, float y, float z);
 ~sPyramid() {
	cleanup();
 }
 void update(sCamera& camera, double delta) override;
 void draw() override;
 void cleanup();



 

  std::vector<GLfloat> m_Vertices =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};
std::vector<GLuint> m_Indices =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


//buffers and vertex usage



// »»» SHADER PROGRAM «««  
  //shader program is an executable to be used on the gpu
static sShaderProgram m_ShaderProgram;

//»»» TEXTURES «««
//static int m_TextureSlot;
static sTexture m_Texture;


//»»» PYRAMID update VARIABLES«««
float m_ScaleSpeed = 0.f;
bool m_ScalePeaked = false;
float m_ScalePeak = 50.f;

static bool initOnce;


};
}//namespace shb