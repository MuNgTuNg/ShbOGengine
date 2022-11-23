#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


//mine
#include <sUtils.hpp>

//std


/*
    » TODO:: 
        •fullscreen command line option
        •window control
        •system tray icon
        •set height/width function
        •set viewport
*/

namespace shb{

class sWindow{
 public:
    sWindow(int height, int width);

    void initWindow(bool makeCurrent = true);
    void makeContextCurrent();
    void destroy();
    void setIcon(const char*);

    
 
    int m_Width;
    int m_Height;
    GLFWwindow* handle() { return m_Handle; }
    

 private:
    GLFWwindow* m_Handle;
    GLFWimage icon[1] ;
};



}//namespace shb