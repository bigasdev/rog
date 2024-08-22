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
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_scancode.h"
#include "SDL_ttf.h"
#include "SDL_video.h"
#include "SoundManager.hpp"
#include "Timer.hpp"
#include "global.hpp"
#include <cassert>
#include <iostream>

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

  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_ALLOW_HIGHDPI);
  m_sdl_window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, window_flags);
  m_window_size = {800, 600};

  GPU_SetInitWindow(SDL_GetWindowID(m_sdl_window));

  m_sdl_renderer =
      SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED);
  R_ASSERT(m_sdl_renderer != nullptr);
  m_gpu = GPU_Init(1920, 1080, GPU_DEFAULT_INIT_FLAGS);
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

  m_res = new Res();
  m_res->init();

  g_engine = this;
  g_res = m_res;

#if _IMGUI
  GUI::setup(m_sdl_window, m_sdl_renderer);
#endif

  Logger::log("Engine post init");
  m_loaded = true;
}

bool m_moving = false;
void Engine::input() {
  if (!m_loaded)
    return;

  SDL_Event event;

#if _IMGUI
  GUI::event(event);
#endif

  while (SDL_PollEvent(&event)) {
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
if(!m_loaded) {
  return;
}

  Timer::update();
}

void Engine::post_update() {
  if (!m_loaded) {
    return;
  }
#if _DEBUG
  m_profiler->update();
  m_renderer->post_update();
#endif
}

void Engine::draw() {
  if (!m_loaded) {
    return;
  }

  GPU_Clear(m_gpu);
  GPU_ClearColor(m_gpu, {0, 0, 0, 255});

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
