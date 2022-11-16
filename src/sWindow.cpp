#include <sWindow.hpp>

namespace shb{

sWindow::sWindow(int h, int w) : _height(h), _width(w){

}

void sWindow::initWindow(){

      // »»» INIT «««
 //initialise glfw
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
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
    _handle = glfwCreateWindow(_height, _width, "Windowed window", NULL, NULL);
  //}




}


void sWindow::makeContextCurrent(){
 //make window context current
  glfwMakeContextCurrent(_handle);

}

void sWindow::destroy(){
    glfwDestroyWindow(_handle);
}

}//namespace shb
