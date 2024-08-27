#include "Timer.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include "../tools/Logger.hpp"

void Timer::update(){
  frame_count++;
  auto new_time = SDL_GetPerformanceCounter();
  elapsed_time = (double)(new_time - last_time_stamp)/ (double)SDL_GetPerformanceFrequency();
  last_time_stamp = new_time;
  Logger::log("Delta time: " + std::to_string(elapsed_time));

  elapsed_time = std::min(elapsed_time, max_delta_time);
  accumulator += elapsed_time;
  current_dt = elapsed_time;
}

double Timer::get_tmod(){
  return dt;
}

double Timer::get_dt(){
  return current_dt;
}

double Timer::get_accumulator(){
  return accumulator;
}

float Timer::get_fps(){
  return 1/current_dt;
}

int Timer::get_frame_count(){
  return frame_count;
}

void Timer::skip(){
  last_time_stamp = SDL_GetPerformanceCounter();
}

void Timer::fixed_t(){
  dt = fixed_dt;
  accumulator -= fixed_dt;
}
