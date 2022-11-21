#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//mine
#include <sUtils.hpp>

//std


/*
    » TODO:: 
        •fullscreen command line options
        •window control
        •system tray icon
*/

namespace shb{

class sWindow{
 public:
    sWindow(int height, int width);

    void initWindow(bool makeCurrent);
    void makeContextCurrent();
    void destroy();
    void setIcon(const char*);

    
 
    int _width;
    int _height;
    GLFWwindow* handle() { return m_Handle; }
    

 private:
    GLFWwindow* m_Handle;
    GLFWimage icon[1] ;
};



}//namespace shb