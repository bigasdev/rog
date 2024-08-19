/**
  @description starting point of the game, act as a boot to load the Engine and
targetting it to the corect platform
**/

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#endif

#include "Timer.hpp"
#include <iostream>

void loop() {
#ifdef __EMSCRIPTEN__
  // mainloop
#endif

#ifdef __EMSCRIPTEN__
  emscripten_cancel_main_loop();
#endif
}

int main(int args, char *argv[]) {
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#else
  loop();
#endif
  Timer::dt = 60.0f;
  std::cout << "Timer::dt: " << Timer::dt << std::endl;
  return 0;
}
