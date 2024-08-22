#pragma once 
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../tools/Common.hpp"
#include "SDL_ttf.h"

class GPU_Target;

class Renderer{
public: 
  Renderer(GPU_Target* gpu);
  ~Renderer();

  void post_update();

  int get_calls() { return m_calls; }

  void draw_rect(Rect rect, Color color, bool fill = false);
  void draw_line(Line line, Color color);
  void draw_text(vec2 pos, const char* text, TTF_Font *font, Color color = {255,255,255,255}, int size = 1, int width = 128);
private:
  GPU_Target* m_gpu;

  int m_calls = 0;
};

#endif
