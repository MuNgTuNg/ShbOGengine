
#pragma once 
#include <geometry/sShapes.hpp>
#include <sWindow.hpp>

namespace shb{

//can be rendered using doubles, is only being rendered using floats at the moment 

class sMandelbrot : public sShape{
   public:
    const std::string name = "MandelBrot";
    
    sMandelbrot (float x , float y , float z);
    void update(sCamera& camera, double delta) override;
    void draw() override;
    void cleanup() override;
    void getInput();
    void listenWindow(sWindow* window){ m_Window = window;}
    void listenCamera(sCamera* camera){ m_Camera = camera;}

    std::vector<GLfloat> m_Vertices = 
    { //     COORDINATES     /        COLORS      /   TexCoord  //
      -1.f, -1.f,  0.f,  
      -1.f, 1.f,   0.f,  
      1.f,  1.f,    0.f,
      1.f,  -1.f,   0.f,
    };
   
    std::vector<GLuint> m_Indices = 
    {
      0,1,2,
      0,2,3
    };


    vertVAO m_VAO{};

    float offsetX = 0;
    float offsetY = 0;
    float m_Zoom = 1.f;
    sWindow* m_Window;
    sCamera* m_Camera;

    
    static sShaderProgram m_ShaderProgram;
    static bool initOnce;
};

}//namespace shb