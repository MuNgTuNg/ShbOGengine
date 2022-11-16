#pragma once

//std
#include <iostream>
#include <string.h>

//mine

//external
#include <glad/glad.h>
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