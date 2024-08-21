#pragma once 
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../tools/Common.hpp"

class GPU_Target;

class Renderer{
public: 
  Renderer(GPU_Target* gpu);
  ~Renderer();

  void draw_rect(Rect rect, Color color);
  void draw_line(Line line, Color color);
private:
  GPU_Target* m_gpu;
};

#endif
