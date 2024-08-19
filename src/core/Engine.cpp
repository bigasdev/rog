#include "Engine.hpp"
#include "SDL_video.h"
#include "Timer.hpp"
#include "SDL.h"
#include "SDL_gpu.h"
#include <cassert>
#include <iostream>
#include "../tools/Logger.hpp"
#include "Assert.hpp"

Engine::Engine(){
  Logger::setup_crash_handlers();
}

Engine::~Engine(){
}

void Engine::init(){
  auto init = SDL_Init(SDL_INIT_EVERYTHING);
  R_ASSERT(init == 0);

  if(init == 0){
    Logger::log("SDL2 initialized");
    Logger::log_group("SDL2 version", SDL_GetRevision());
  }

  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, window_flags);
  R_ASSERT(window != nullptr);

  if(window != nullptr){
    Logger::log("SDL2 window created");
  }

  GPU_SetInitWindow(SDL_GetWindowID(window));
}

void Engine::input(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    if(event.type == SDL_QUIT){
      m_running = false;
    }
  }
}

void Engine::update(){
  Timer::update();
}

void Engine::quit(){
  SDL_DestroyWindow(SDL_GetWindowFromID(GPU_GetInitWindow()));
  SDL_Quit();
  Logger::log("SDL2 quit");
  Logger::write_to_file("log.txt");
}
