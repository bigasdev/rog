#include "Timer.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

void Timer::update(){
  frame_count++;
  auto new_time = SDL_GetPerformanceCounter();
  elapsed_time = (double)(new_time - last_time_stamp)/ (double)SDL_GetPerformanceFrequency();
  last_time_stamp = new_time;
  if(elapsed_time < max_delta_time){
    current_dt = std::lerp(elapsed_time, current_dt, smooth_factor);
  }else{
    elapsed_time = 1 / wanted_fps;
  }
  dt = current_dt;
}

float Timer::get_tmod(){
  return dt * wanted_fps;
}

float Timer::get_fps(){
  return 1/dt;
}

int Timer::get_frame_count(){
  return frame_count;
}

void Timer::skip(){
  last_time_stamp = SDL_GetPerformanceCounter();
}
