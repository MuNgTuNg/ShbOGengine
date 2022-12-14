#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <sWindow.hpp>


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
  TinkeringWindow(sWindow& window) : sGUI(window) {
  }
  void update() override { 
    beginWindow("Tinkering Window");
    float value = 444;
    ImGui::DragFloat("No value chosen",&value,0.01);
    ImGui::DragFloat("No value chosen", &value,0.01);
  };
  void update(float& scale, 
              float& angle,
              float& x,float& y,float& z, 
              float& fov,
              double& fps) {

    float moveSpeed = 2.f * (fps/1000);
    //imgui stuff
    beginWindow("Tinkering Window");
    ImGui::Text("MSPF: %fms", fps);
    ImGui::Text("FPS: %fms", 1/(fps/1000));
    ImGui::DragFloat("Rotation",&angle,moveSpeed);
    ImGui::DragFloat("x",&x,moveSpeed);
    ImGui::DragFloat("y",&y,moveSpeed);
    ImGui::DragFloat("z",&z,moveSpeed);
    ImGui::DragFloat("FOV",&fov,moveSpeed);
    ImGui::DragFloat("Scale",&scale,moveSpeed);
    endWindow();

  }
};
}