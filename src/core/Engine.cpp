#include "Engine.hpp"
#include "../tools/Logger.hpp"
#include "../tools/Profiler.hpp"
#include "Assert.hpp"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_gpu.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_scancode.h"
#include "SDL_ttf.h"
#include "SDL_video.h"
#include "Timer.hpp"
#include <cassert>
#include <iostream>

struct test {
  int a;
  int b;
};

std::vector<test *> tests;

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
  SDL_Window *window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       800, 600, window_flags);

  GPU_SetInitWindow(SDL_GetWindowID(window));

  m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  R_ASSERT(m_renderer != nullptr);
  m_gpu = GPU_Init(800, 600, GPU_DEFAULT_INIT_FLAGS);
  R_ASSERT(m_gpu != nullptr);

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

  R_ASSERT(window != nullptr);

  if (window != nullptr) {
    Logger::log("SDL2 window created");
  }

  m_running = true;
}

void Engine::post_init() {
  if (m_loaded) {
    return;
  }

  m_profiler = new Profiler();

  Logger::log("Engine post init");
  m_loaded = true;
}

bool m_moving = false;
void Engine::input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
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
      case SDL_SCANCODE_E:
        for (int i = 0; i < 10000; i++) {
          tests.push_back(new test());
        }
        break;
      }
    }
  }
}

void Engine::update() {
  m_profiler->update();

  Timer::update();
}

void Engine::draw() {
  GPU_Clear(m_gpu);
  GPU_ClearColor(m_gpu, {0, 0, 0, 255});
  GPU_SetVirtualResolution(m_gpu, 800, 600);
  GPU_Flip(m_gpu);
}

void Engine::quit() {
  SDL_DestroyWindow(SDL_GetWindowFromID(GPU_GetInitWindow()));
  SDL_Quit();
  Logger::log("SDL2 quit");
  Logger::write_to_file("log.txt");
}
