#if _IMGUI
#include "AppGui.hpp"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_sdl.h"
#include "../ImGui/imgui_impl_sdlrenderer.h"
#include "../imgui/imgui_impl_opengl3.h"

SDL_Window* GUI::gui_window = nullptr;
SDL_GLContext GUI::gui_renderer = nullptr;

void GUI::setup(SDL_Window *window, SDL_GLContext& renderer) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  // io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

  // styling
  ImGuiStyle &style = ImGui::GetStyle();
  style.WindowRounding = 5;
  style.WindowTitleAlign = ImVec2(0.05f, 0.5f);
  style.WindowBorderSize = 0;
  style.FrameRounding = 2;
  style.ScrollbarRounding = 0;
  style.FramePadding = ImVec2(4, 2);
  style.ChildRounding = 5;
  // style.Colors[ImGuiCol_Button] = ImVec4{0.25f, 0.29f, 0.43f, 0};
  // style.Colors[ImGuiCol_ChildBg] = ImVec4{0.15f, 0.15f, 0.15f, 1};
  // style.Colors[ImGuiCol_WindowBg] = ImVec4{0.25f, 0.29f, 0.43f, 0};
  // style.Colors[ImGuiCol_Header] = ImVec4{0.25f, 0.29f, 0.43f, 0};
  // style.Colors[ImGuiCol_ButtonActive] = ImVec4{0.34f, 0.43f, 0.25f, 0};
  // style.Colors[ImGuiCol_ButtonHovered] = ImVec4{0.39f, 0.45f, 0.57f, 1.0f};
  // style.Colors[ImGuiCol_Border] = ImVec4{0.39f, 0.45f, 0.57f, .4f};
  // style.Colors[ImGuiCol_TitleBg] = ImVec4{0.25f, 0.29f, 0.43f, 1.0f};
  // style.Colors[ImGuiCol_TitleBgActive] = ImVec4{0.34f, 0.43f, 0.25f, 1.0f};

  // adding custom font
  io.Fonts->AddFontFromFileTTF("res/font/pixolleta.ttf", 10);

  // ImGui::StyleColorsDark();

  GUI::gui_window = window;
  GUI::gui_renderer = renderer;

  ImGui_ImplSDL2_InitForOpenGL(window, renderer);
  ImGui_ImplOpenGL3_Init("#version 130");
}

void GUI::event(SDL_Event event) { ImGui_ImplSDL2_ProcessEvent(&event); }

void GUI::draw(std::function<void()> function) {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(GUI::gui_window);
  ImGui::NewFrame();

  // add here our GUI render
  {
    if (function)
      function();
    bool isOpen = true;
    ImGui::ShowDemoWindow(&isOpen);

    // example of a window
    /*
    ImGui::Begin("Hello World!");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f /
    ImGui::GetIO().Framerate, ImGui::GetIO().Framerate); ImGui::End();
    */
  }

  // rendering
  ImGui::Render();
  SDL_GL_MakeCurrent(GUI::gui_window, GUI::gui_renderer);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::clean() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

// we will check some stuff so we can focus the keyboard without breaking
// anything else
void GUI::set_focus() {
  if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
    ImGui::SetKeyboardFocusHere(0);
}
#else 
#include "AppGui.hpp"

SDL_Window* GUI::gui_window = nullptr;
SDL_GLContext GUI::gui_renderer = nullptr;

void GUI::setup(SDL_Window *window, SDL_GLContext& renderer) {}
void GUI::event(SDL_Event event) {}
void GUI::draw(std::function<void()> function) {}
void GUI::clean() {}
void GUI::set_focus() {}

#endif
