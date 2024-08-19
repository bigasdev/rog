/**
  @description not so much to say about this one, is the engine of the game, here we will instantiate and run everything
**/

#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

class SDL_Renderer;
class GPU_Target;

class Engine{
public:
  Engine();
  ~Engine();

  void init();
  void update();
  void input();
  void draw();
  void quit();
  bool is_running() { return m_running; }
private:
  bool m_running = true;

  SDL_Renderer* m_renderer;
  GPU_Target* m_gpu;
};

#endif
