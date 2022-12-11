#include <sWindow.hpp>
#include <stb_image.h>


namespace shb{

sWindow::sWindow(int h, int w) : m_Height(h), m_Width(w){

}


void sWindow::update(int height, int width){ //updates clear color and viewport to match h and w of window
  //set clear color
  glClearColor(0.5f,0.f,0.f,1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  if(height != 0 && width !=0){
    m_Height = height;
    m_Width = width;
    glViewport(0,0,height,width);
    return;
  }
  
  int display_w, display_h;
  glfwGetFramebufferSize(m_Handle, &display_w, &display_h);
  glViewport(0,0,display_w,display_h);
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

 //set to fullscreen or windowed based on command line arguments //TODO
//   if( argv[1]!= NULL && strcmp(argv[1], "fullscreen") == 0)
//   {
//     height = videomode->height;
//     width = videomode->width;
//     window = glfwCreateWindow(height, width, "Fullscreen window", monitor, NULL);
//   }
//   else
//   {
    m_Handle = glfwCreateWindow(m_Height, m_Width, "Windowed window", NULL, NULL);
  //}
    
    if(makeCurrent){

       glfwMakeContextCurrent(m_Handle);
       setIcon("../resources/icon.jpeg");
       //glad is loaded on current context so it must be after window creation and 
       //contextualisation
       gladLoadGL();
       // During init, enable debug output


       //set the viewport            
       glViewport(0,0,m_Height,m_Width);
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
  stbi_image_free(pixels);
}

void sWindow::makeContextCurrent(){
 //make window context current
  glfwMakeContextCurrent(m_Handle);

}

void sWindow::destroy(){
    
    glfwDestroyWindow(m_Handle);
}

}//namespace shb
