/** 
  @description used as a global time measurement tool, this will handle all the fps calculatino for dt (delta time) and fixed update stuff
**/

#ifndef TIMER_HPP
#define TIMER_HPP

#include "SDL.h"
#include "SDL_timer.h"

namespace Timer{
  static float wanted_fps = 60.0f;

  static float max_delta_time = 0.5;

  static float smooth_factor = 0.95f;

  static float last_time_stamp = SDL_GetPerformanceCounter();

  static float elapsed_time = 0.0f;

  static int frame_count = 0;

  static float dt = 1 / wanted_fps;
  static float current_dt = 1 / wanted_fps;

  static float fps = 0.0f;
  static float tmod = 0.0f;

  void update();
  float get_tmod();
  float get_fps();
  void skip();
}


#endif
