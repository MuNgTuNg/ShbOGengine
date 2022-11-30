#pragma once

//std
#include <iostream>
#include <string.h>

//mine
#include <shapes.hpp>
#include <sShader.hpp>
#include <sWindow.hpp>

//external

//imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//glfw/glad
#include <glad/glad.h> //include glad/glad.h instead of glad.c to avoid multiple definitions of functions as glad likes to cry about this
#include <GLFW/glfw3.h> 
#include <stb_image.h>

//maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//
//
//
//
//
//  TODO: » abstract and clean up
//        » logging system
//        » change shader system to use string instead of VECTORS????
//
//
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


 private:
   sWindow m_Window{1000,1000};

   //these should be abstracted into classes
   GLuint m_VAO, m_VBO, m_IBO;
   GLuint m_ShaderProgram;

   
};


}//namespace shb