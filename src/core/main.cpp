/**
  @description starting point of the game, act as a boot to load the Engine and
targetting it to the corect platform
**/
#ifndef MAIN_HPP
#define MAIN_HPP

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

#include "Engine.hpp"
#include "Assert.hpp"
#include "Timer.hpp"
#include <iostream>
#include <memory>

std::unique_ptr<Engine> engine;

void setup() {
  engine = std::make_unique<Engine>();
  engine->init();
}

void loop() {
#ifdef __EMSCRIPTEN__
  // mainloop
#elif __WIN32__
  while (engine->is_running()) {
    engine->input();
    engine->update();
  }
#endif

#ifdef __EMSCRIPTEN__
  emscripten_cancel_main_loop();
#endif
}

int main(int args, char *argv[]) {
  setup();

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#else
  loop();
#endif

  engine->quit();
  return 0;
}
#endif
