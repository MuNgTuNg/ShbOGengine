#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <sWindow.hpp>
#include <sCamera.hpp>
#include <sShapes.hpp>


#include <string>

namespace shb{

//once different functionalities emerge from this GUI class i can have polymorphic 
//derived classes that serve different purposes (like sGUI* moniter = new heartMoniter(); or sGUI* display = new debugDisplay();)


class sGUI{
 public:
    sGUI(sWindow& window); //options for creation, probably use an enum
    ~sGUI(); 
    sGUI(const sGUI&) = delete;

    virtual void update() = 0;

 public:
   void initGUI();
   void startFrame();
   void endWindow();
   void destroyGUI();
   void render();
   void beginWindow(const std::string& name);
 private:
   sWindow& m_Window;


};


class DefaultGUI : public sGUI{
 public:
  DefaultGUI(sWindow& window) : sGUI(window) {}

  void update() override {
    beginWindow("Default Window");
    endWindow();

  }
};

class TinkeringWindow : public sGUI{
 public:
  std::string m_Name;
  

  TinkeringWindow(sWindow& window, const char * name) : sGUI(window) {
    m_Name = name;
  }
  void update() override { 
    beginWindow("Tinkering Window");
    float value = 444;
    ImGui::DragFloat("No value chosen",&value,0.01);
    ImGui::DragFloat("No value chosen", &value,0.01);
  };

  double timer = 0;
  
  void update(sCamera& camera,
              sPyramid& pyramid,
              double& delta,
              float& scale
             )
              { //delta in ms
    
    

 
    //imgui stuff
    beginWindow(m_Name);

    ImGui::Text("MSPF: %fms", delta*1000);         //todo make this legible at runtime
    ImGui::Text("FPS: %fms", 1/(delta));
    
    float pyraMoveSpeed = 200.f * delta;
    //ImGui::DragFloat("Rotation",&pyramid.m_Angle,pyraMoveSpeed);
    //ImGui::DragFloat("RotX",&pyramid.m_RotAxisx,pyraMoveSpeed);
    //ImGui::DragFloat("Roty",&pyramid.m_RotAxisy,pyraMoveSpeed);
    //ImGui::DragFloat("RotZ",&pyramid.m_RotAxisz,pyraMoveSpeed);

    ImGui::Text("Camera rot axis x: %f", camera.m_RotX);
    ImGui::Text("Camera rot axis y: %f", camera.m_RotY);
    ImGui::Text("Camera rot axis z: %f", camera.m_RotZ);

    ImGui::DragFloat("x",&camera.m_X,camera.m_MoveSpeed);
    ImGui::DragFloat("y",&camera.m_Y,camera.m_MoveSpeed);
    ImGui::DragFloat("z",&camera.m_Z,camera.m_MoveSpeed);
    ImGui::DragFloat("FOV",&camera.m_Fov,camera.m_MoveSpeed);
    ImGui::DragFloat("Move Speed",&camera.m_MoveSpeed,0.4f);
    
    //ImGui::DragFloat("Scale",&scale,pyraMoveSpeed);
    endWindow();

  }
};
}