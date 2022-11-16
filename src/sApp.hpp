#pragma once

//std
#include <iostream>
#include <string.h>

//mine
#include <shapes.hpp>
#include <sShaders.hpp>
#include <sWindow.hpp>

//external
#include <glad/glad.h> //include glad/glad.h instead of glad.c to avoid multiple definitions of functions as glad likes to cry about this
#include <GLFW/glfw3.h> 



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
   sWindow _window{1000,1000};
   GLuint _VAO, _VBO, _IBO;
   GLuint _shaderProgram;

   
};


}//namespace shb