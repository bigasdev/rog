/**
  @description not so much to say about this one, is the engine of the game,
here we will instantiate and run everything
**/

#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

class SDL_Renderer;
class GPU_Target;
class Profiler;
class Renderer;
class Res;

class Engine {
private:
  bool m_running = false;
  bool m_loaded = false;

  SDL_Renderer *m_sdl_renderer;
  GPU_Target *m_gpu;
  Profiler *m_profiler;
  Renderer *m_renderer;
  Res *m_res;

public:
  Engine();
  ~Engine();

  void init();
  void post_init();
  void update();
  void input();
  void draw();
  void quit();
  bool is_running() { return m_running; }

  //getters 
  Renderer *get_renderer() { return m_renderer; }
};

#endif
