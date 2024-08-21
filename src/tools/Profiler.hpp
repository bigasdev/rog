#pragma once 

#ifndef PROFILER_HPP
#define PROFILER_HPP

#define PROFILER_TICK 60

class Profiler{
public: 
  Profiler();
  ~Profiler();

  void update();
  void print();
private:
  int m_tick_count;
};

#endif
