/**
  @description not so much to say about this one, is the engine of the game, here we will instantiate and run everything
**/

#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine{
public:
  Engine();
  ~Engine();

  void init();
  void update();
  void input();
  void quit();
  bool is_running() { return m_running; }
private:
  bool m_running = true;
};

#endif
