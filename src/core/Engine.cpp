#include "Engine.hpp"
#include "../tools/Logger.hpp"
#include "Assert.hpp"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_gpu.h"
#include "SDL_scancode.h"
#include "SDL_video.h"
#include "Timer.hpp"
#include <cassert>
#include <iostream>

Engine::Engine() { Logger::setup_crash_handlers(); }

Engine::~Engine() {}

void Engine::init() {
  auto init = SDL_Init(SDL_INIT_EVERYTHING);

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

  R_ASSERT(window != nullptr);

  if (window != nullptr) {
    Logger::log("SDL2 window created");
  }
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
      }
    }
  }
}

  void Engine::update() { Timer::update(); }

  void Engine::draw() {
    GPU_Clear(m_gpu);
    GPU_SetVirtualResolution(m_gpu, 800, 600);
    GPU_Flip(m_gpu);
  }

  void Engine::quit() {
    SDL_DestroyWindow(SDL_GetWindowFromID(GPU_GetInitWindow()));
    SDL_Quit();
    Logger::log("SDL2 quit");
    Logger::write_to_file("log.txt");
  }
