#include <sGui.hpp>

namespace shb{


sGUI::sGUI(sWindow& window) : m_Window(window){
    IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(m_Window.handle(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
}
sGUI::~sGUI() {}

void sGUI::startFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}


void sGUI::render(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void sGUI::beginWindow(const std::string& name = "No name window"){
    const char* str = &name[0];
    ImGui::Begin(str);
}

void sGUI::endWindow() {
    ImGui::End();
}



void sGUI::destroyGUI() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}





}//namespace shb