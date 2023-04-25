#pragma once

//»»»std«««
#include <iostream>
#include <string.h>

//»»»mine«««

#include <sShader.hpp>
#include <geometry/sShapes.hpp>
#include <sWindow.hpp>
#include <sGui.hpp>
#include <sBuffer.hpp>
#include <sTexture.hpp>
#include <sCamera.hpp>

//»»»external«««
//glfw/glad
#include <glad/glad.h> //include glad/glad.h instead of glad.c to avoid multiple definitions of functions as glad likes to cry about this
#include <GLFW/glfw3.h> 
#include <stb_image.h>

//maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace shb{

  //vector of all objects

  //TODO
  //std::vector<std::vector<sShape*>> allObjects;

class sApp{
 public:
    sApp();
    ~sApp();
    sApp(const sApp&) = delete;
    sApp (sApp&&) = delete;

    void run();
    void cleanup();
    bool m_Closed = false;


 private:
   sWindow m_Window{1920,1080};
   sCamera m_Camera{m_Window};
   
   sCameraGUI cameraWindow{m_Window, "Camera"};
   sObjectGUI objectsWindow{m_Window, "Objects"};

   void getInput();

   //shapes
   std::vector<sPyramid> pyramids{};
   std::vector<sIcosohedron> icosohedrons{};
    

   //fractals
   sQuad quad{0.f,-10.f,-10.f};
   sMandelbrot mandel{0.f,0.f,-1.f};
   
   bool juliaStart = true;
   sJulia julia{0.f,0.f,-1.f};

   double m_PreviousFrameTime = glfwGetTime();
   double m_CurrentFrameTime;
   double m_DeltaTime;
   double m_FrameTimeInMS;

 
};

}//namespace shb