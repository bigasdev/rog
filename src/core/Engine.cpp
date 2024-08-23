#include "Engine.hpp"
#include "../renderer/AppGui.hpp"
#include "../renderer/Renderer.hpp"
#include "../res/Res.hpp"
#include "../tools/Logger.hpp"
#include "../tools/Profiler.hpp"
#include "Assert.hpp"
#include "InputManager.hpp"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_gpu.h"
#include "SDL_hints.h"
#include "SDL_image.h"
#include "SDL_keycode.h"
#include "SDL_mixer.h"
#include "SDL_render.h"
#include "SDL_scancode.h"
#include "SDL_ttf.h"
#include "SDL_video.h"
#include "SoundManager.hpp"
#include "Timer.hpp"
#include "global.hpp"
#include "../tools/Math.hpp"
#include <cassert>
#include <iostream>

bool moving_right = false;
bool moving_left = false;
float x = -200;

Engine::Engine() { Logger::setup_crash_handlers(); }

Engine::~Engine() {}

void Engine::init() {
  int init = -99;
#ifdef __EMSCRIPTEN__
  init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
#else
  init = SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO);
#endif

  R_ASSERT(init == 0);

  if (init == 0) {
    Logger::log("SDL2 initialized");
    Logger::log_group("SDL2 version", SDL_GetRevision());
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
  m_sdl_window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, window_flags);
  m_window_size = {800, 600};

  GPU_SetInitWindow(SDL_GetWindowID(m_sdl_window));

  m_sdl_renderer =
      SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED);
  R_ASSERT(m_sdl_renderer != nullptr);
  m_gpu = GPU_Init(1920, 1080, 0);
  R_ASSERT(m_gpu != nullptr);

  GPU_SetWindowResolution(m_window_size.x, m_window_size.y);

  if (m_renderer != nullptr && m_gpu != nullptr) {
    Logger::log("SDL2 renderer created");
    Logger::log("SDL2 GPU created");
  }
  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
    Logger::log("SDL2 image initialized");
  }

  SDL_GL_SetSwapInterval(1);

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0) {
    Logger::log("SDL2 mixer initialized");
  } else {
    Logger::log("SDL2 mixer failed to initialize " +
                std::string(Mix_GetError()));
  }

  TTF_Init();

  R_ASSERT(m_sdl_window != nullptr);

  if (m_sdl_window != nullptr) {
    Logger::log("SDL2 window created");
  }

  m_running = true;
}

void Engine::post_init() {
  if (m_loaded) {
    return;
  }

  m_profiler = new Profiler();
  m_renderer = new Renderer(m_gpu);
  m_sound_manager = new SoundManager();
  m_input_manager = new InputManager();
  g_sound_manager = m_sound_manager;
  g_input_manager = m_input_manager;
  g_input_manager->bind_keyboard(SDLK_e, &moving_right);
  g_input_manager->bind_keyboard(SDLK_q, &moving_left);

  m_res = new Res(m_sdl_renderer);
  m_res->init();

  m_renderer->init_shader(m_res->get_shaders());

  g_engine = this;
  g_res = m_res;

#if _IMGUI
  GUI::setup(m_sdl_window, m_sdl_renderer);
#endif

  m_camera = new GPU_Camera{0, 0, 0, 0, 4, 4, 1, 1};

  Logger::log("Engine post init");
  m_loaded = true;
}

bool m_moving = false;
void Engine::input() {
  if (!m_loaded)
    return;

  SDL_Event event;

#if _IMGUI
  // GUI::event(event);
#endif
  while (SDL_PollEvent(&event) != 0) {
    g_input_manager->update(event);
    switch (event.type) {
    case SDL_WINDOWEVENT:
      if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        // updating window size
        {
          int h = 0, w = 0;
          SDL_GetWindowSize(m_sdl_window, &h, &w);
          m_window_size.x = h;
          m_window_size.y = w;
          GPU_SetWindowResolution(h, w);
        }
      }
      break;
    case SDL_QUIT:
      m_running = false;
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.scancode) {
      case SDL_SCANCODE_ESCAPE:
#if _DEBUG
        m_running = false;
#endif
        break;
      }
    }
  }
}

void Engine::update() {
  if (!m_loaded) {
    return;
  }

  x = Math::lerp(x, 100, 9 * Timer::get_tmod());
}

void Engine::post_update() {
  if (!m_loaded) {
    return;
  }
#if _DEBUG
  m_profiler->update();
  m_renderer->post_update();
  m_res->update();
#endif
}

void Engine::draw() {
  if (!m_loaded) {
    return;
  }

  GPU_Clear(m_gpu);
  GPU_SetCamera(m_gpu, m_camera);
  // game draw
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      //m_renderer->draw_from_sheet(*m_res->get_texture("concept"),
                                  //{i * 8, j * 8}, {0, 0, 8, 8});
    }
  }
  m_renderer->draw_from_sheet(*m_res->get_texture("concept"), {x, 20.f},
                              {0, 1, 8, 8});
  GPU_SetCamera(m_gpu, nullptr);

#if _DEBUG
  m_profiler->draw();
#endif

#if _IMGUI
#endif

  GPU_Flip(m_gpu);
}

void Engine::quit() {
  SDL_DestroyWindow(SDL_GetWindowFromID(GPU_GetInitWindow()));
  SDL_Quit();
  Logger::log("SDL2 quit");
  Logger::write_to_file("log.txt");
}
