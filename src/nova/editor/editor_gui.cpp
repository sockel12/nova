#include <nova/editor/editor_gui.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <nova/application.h>

#include <nova/editor/windows/hierarchy_window.h>
#include <nova/editor/windows/inspector_window.h>
#include <nova/editor/windows/graphics_window.h>
#include <nova/editor/windows/scene_window.h>
#include <nova/editor/windows/scene_settings_window.h>
#include <nova/editor/windows/resource_manager_window.h>
#include <nova/editor/windows/resource_viewer_window.h>

namespace nova::editor
{

Ref<EditorGUIContext> EditorGUI::s_context = std::make_shared<EditorGUIContext>();
std::vector<Ref<EditorGUIWindow>> EditorGUI::s_windows = {};
bool EditorGUI::s_demo_window_visible = true;

void EditorGUI::init()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(Application::instance()->window()->native_window(), true);
  ImGui_ImplOpenGL3_Init("#version 330");

  register_window<editor::windows::HierarchyWindow>("Hierarchy");
  register_window<editor::windows::InspectorWindow>("Inspector");
  register_window<editor::windows::GraphicsWindow>("Graphics");
  register_window<editor::windows::SceneWindow>("Scene");
  register_window<editor::windows::SceneSettingsWindow>("Scene Settings");
  register_window<editor::windows::ResourceManagerWindow>("Resource Manager");
  register_window<editor::windows::ResourceViewerWindow>("Resource Viewer");
}

void EditorGUI::shutdown()
{
  s_context.reset();
  s_windows.clear();

  ImGui_ImplGlfw_Shutdown();
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}

void EditorGUI::render(const Ref<core::Scene>& current_scene)
{
  s_context->active_scene = current_scene;

  begin();

  if (s_demo_window_visible)
    ImGui::ShowDemoWindow();

  for (const auto& window : s_windows)
  {
    if (window->visible())
      window->render(*s_context);
  }

  end();
}

void EditorGUI::begin()
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::DockSpaceOverViewport();

  menu_bar();
}

void EditorGUI::menu_bar()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Windows"))
    {
      for (const auto& window : s_windows)
      {
        if (ImGui::MenuItem(window->name().c_str()))
        {
          window->visible(!window->visible());
        }
      }

      if (ImGui::MenuItem("Demo Window"))
      {
        s_demo_window_visible = !s_demo_window_visible;
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}

void EditorGUI::end()
{
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}  // namespace nova::editor