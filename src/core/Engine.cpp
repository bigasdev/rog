#include "Engine.hpp"
#include "SDL_video.h"
#include "Timer.hpp"
#include "SDL.h"
#include "SDL_gpu.h"
#include <iostream>

Engine::Engine(){
}

Engine::~Engine(){
}

void Engine::init(){
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, window_flags);
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
  std::cout << "FPS: " << Timer::get_fps() << std::endl;
  std::cout << "Tmod: " << Timer::get_tmod() << std::endl;
}
