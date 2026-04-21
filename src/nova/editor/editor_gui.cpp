#include <nova/editor/editor_gui.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <nova/application.h>

namespace nova::editor
{

Ref<EditorGUIContext> EditorGUI::s_context = std::make_shared<EditorGUIContext>();
std::vector<Ref<EditorGUIWindow>> EditorGUI::s_windows = {};

void EditorGUI::init()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void) io;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(Application::instance()->window()->native_window(), true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void EditorGUI::shutdown()
{
  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}

void EditorGUI::render(const Ref<core::Scene>& current_scene)
{
  s_context->active_scene = current_scene;

  begin();

  ImGui::ShowDemoWindow();

  for (const auto& window : s_windows)
  {
    window->render(*s_context);
  }

  end();
}

void EditorGUI::begin()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void EditorGUI::end()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}  // namespace nova::editor