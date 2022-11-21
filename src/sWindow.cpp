#include <sWindow.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace shb{

sWindow::sWindow(int h, int w) : _height(h), _width(w){

}

void sWindow::initWindow(bool makeCurrent){

      // »»» INIT «««
 //initialise glfw
  if (!glfwInit())
  {
    DEBUGLOG("Failed to initialize GLFW\n");
    exit(EXIT_FAILURE);
  }
    // »»» WINDOW «««
 //tell opengl what min and max version we are using
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

 //tell opengl we're using the core profile (only using the modern functions)
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

 //get the handle to the primary monitor and get details about said moniter
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* videomode = glfwGetVideoMode(monitor);

 //set to fullscreen or windowed based on command line arguments
//   if( argv[1]!= NULL && strcmp(argv[1], "fullscreen") == 0)
//   {
//     height = videomode->height;
//     width = videomode->width;
//     window = glfwCreateWindow(height, width, "Fullscreen window", monitor, NULL);
//   }
//   else
//   {
    m_Handle = glfwCreateWindow(_height, _width, "Windowed window", NULL, NULL);
  //}
    
    if(makeCurrent){

       glfwMakeContextCurrent(m_Handle);
       setIcon("../resources/icon.jpeg");
    }



}

void sWindow::setIcon(const char* filePath){

  //height and width variables
  //get height, width,channels and pixels of image from stbiload
  //use that to create GLFWimage
  //glfwSetwindowIcon

  int height, width, channels;

  unsigned char* pixels = stbi_load(filePath,&width,&height,&channels,4);
  
  icon[0].height = height;
  icon[0].width  = width;
  icon[0].pixels = pixels;

  glfwSetWindowIcon(m_Handle,1,icon);
}

void sWindow::makeContextCurrent(){
 //make window context current
  glfwMakeContextCurrent(m_Handle);

}

void sWindow::destroy(){
    glfwDestroyWindow(m_Handle);
}

}//namespace shb
