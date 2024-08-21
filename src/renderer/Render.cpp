#include "Renderer.hpp"
#include "SDL_gpu.h"

Renderer::Renderer(GPU_Target* gpu) : m_gpu(gpu) {}

Renderer::~Renderer() {}

void Renderer::draw_rect(Rect rect, Color color) {
  GPU_Rectangle(m_gpu, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, {color.r, color.g, color.b, color.a});
}

void Renderer::draw_line(Line line, Color color) {
  GPU_Line(m_gpu, line.x1, line.y1, line.x2, line.y2, {color.r, color.g, color.b, color.a});
}
