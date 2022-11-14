#pragma once

//std
#include <iostream>
#include <string.h>

//mine

//external
#include <glad/glad.h> //include glad/glad.h instead of glad.c to avoid multiple definitions of functions as glad likes to cry about this
#include <GLFW/glfw3.h> 


namespace shb{

class sApp{
 public:
    sApp();
    sApp(const sApp&) = delete;
    sApp (sApp&&) = delete;

    void run();
 private:

};


}//namespace shb