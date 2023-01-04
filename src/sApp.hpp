#pragma once

//»»»std«««
#include <iostream>
#include <string.h>

//»»»mine«««

#include <sShader.hpp>
#include <sShapes.hpp>
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

//
//
//
//
//
//  TODO: » abstract and clean up more
//        » change shader system to use string instead of VECTORS????
//        » 3D 3D 3D
//        » textures
//
//
//



namespace shb{

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
   TinkeringWindow tinkerWindow{m_Window, "Tinker1"};

   std::vector<sPyramid> pyramids{};


   double m_PreviousFrameTime = glfwGetTime();
   double m_CurrentFrameTime;
   double m_DeltaTime;
   double m_FrameTimeInMS;
   
};


}//namespace shb