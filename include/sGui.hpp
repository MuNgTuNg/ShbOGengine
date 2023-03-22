#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <sWindow.hpp>
#include <sCamera.hpp>
#include <geometry/sShapes.hpp>

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

class CameraWindow : public sGUI{
 public:
  std::string m_Name;
  float x = 0.f,y = 0.f,z =0.f;

  CameraWindow(sWindow& window, const char * name) : sGUI(window) {
    m_Name = name;
  }

  void update() override { 
    beginWindow("Tinkering Window");
    float value = 444;
    ImGui::DragFloat("No value chosen",&value,0.01);
    ImGui::DragFloat("No value chosen", &value,0.01);
  };

  double timer = 0;
  
  void update(sCamera* camera, double& delta){ 
    //delta in ms
    beginWindow(m_Name);

    ImGui::Text("MSPF: %fms", delta*1000);         //todo make this legible at runtime
    ImGui::Text("FPS: %fms", 1/(delta));

  
    ImGui::Text("Press C to capture mouse");
    ImGui::Text("Press X to release mouse");

    ImGui::DragFloat("x",&camera->m_Position.x,camera->m_MoveSpeed);
    ImGui::DragFloat("y",&camera->m_Position.y,camera->m_MoveSpeed);
    ImGui::DragFloat("z",&camera->m_Position.z,camera->m_MoveSpeed);

    ImGui::DragFloat("FOV",&camera->m_Fov,camera->m_MoveSpeed);
    ImGui::DragFloat("Move Speed",&camera->m_MoveSpeed,0.4f);
    
    ImGui::Checkbox("Movement", &camera->m_KeyboardInput);     
    endWindow();
  }
};
}