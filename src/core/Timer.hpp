/** 
  @description used as a global time measurement tool, this will handle all the fps calculatino for dt (delta time) and fixed update stuff
**/

#ifndef TIMER_HPP
#define TIMER_HPP

#include "SDL.h"
#include "SDL_timer.h"

namespace Timer{
  static double wanted_fps = 60.0f;

  static double max_delta_time = 0.5;

  static double smooth_factor = 0.95f;

  static double last_time_stamp = SDL_GetPerformanceCounter();

  static double elapsed_time = 0.0f;

  static int frame_count = 0;

  static double accumulator = 0.0f;

  static double dt = 1 / wanted_fps;
  static double fixed_dt = 1 / wanted_fps;
  static double current_dt = 1 / wanted_fps;

  static double fps = 0.0f;
  static double tmod = 0.0f;

  void update();
  double get_tmod();
  double get_dt();
  double get_accumulator();
  float get_fps();
  int get_frame_count();
  void skip();
  void fixed_t();
}


#endif
