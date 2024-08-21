#pragma once 

#ifndef PROFILER_HPP
#define PROFILER_HPP

#define PROFILER_TICK 30

class Profiler{
public: 
  Profiler();
  ~Profiler();

  void update();
  void print();
private:
  
};

#endif
