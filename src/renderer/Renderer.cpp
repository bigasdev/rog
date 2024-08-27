#include "Renderer.hpp"
#include "../tools/Logger.hpp"
#include "SDL_gpu.h"

Renderer::Renderer(GPU_Target *gpu) : m_gpu(gpu) {}

Renderer::~Renderer() {}

void Renderer::post_update() { m_calls = 0; }

void Renderer::init_shader(std::vector<std::string> shaders) {}

void Renderer::draw_rect(Rect rect, Color color, bool fill) {
  if (!fill) {
    GPU_Rectangle(m_gpu, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h,
                  {color.r, color.g, color.b, color.a});
  } else {
    GPU_RectangleFilled(m_gpu, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h,
                        {color.r, color.g, color.b, color.a});
  }
  m_calls++;
}

void Renderer::draw_line(Line line, Color color) {
  GPU_Line(m_gpu, line.x1, line.y1, line.x2, line.y2,
           {color.r, color.g, color.b, color.a});
  m_calls++;
}

void Renderer::draw_text(vec2 pos, const char *text, TTF_Font *font,
                         Color color, int size, int width) {
  SDL_Surface *surfaceMessage = TTF_RenderText_Blended_Wrapped(
      font, text, {color.r, color.g, color.b, color.a}, width);
  GPU_Image *message = GPU_CopyImageFromSurface(surfaceMessage);
  GPU_SetImageFilter(message, GPU_FILTER_NEAREST);

  GPU_Rect src;
  src.x = 0;
  src.y = 0;
  src.w = surfaceMessage->w;
  src.h = surfaceMessage->h;

  GPU_Rect dst;
  dst.x = pos.x;
  dst.y = pos.y;
  dst.w = src.w * size;
  dst.h = src.h * size;

  SDL_FreeSurface(surfaceMessage);
  GPU_BlitRect(message, &src, m_gpu, &dst);
  GPU_FreeImage(message);
  m_calls++;
}

void Renderer::draw_from_sheet(GPU_Image *sheet, vec2 pos, Rect l_point) {
  GPU_Rect src;
  src.x = l_point.x * l_point.w;
  src.y = l_point.y * l_point.h;
  src.w = l_point.w;
  src.h = l_point.h;

  GPU_Rect dst;
  dst.x = static_cast<int>(pos.x);
  dst.y = static_cast<int>(pos.y);
  dst.w = src.w;
  dst.h = src.h;

  GPU_BlitRectX(sheet, &src, m_gpu, &dst, 0, 0, 0, GPU_FLIP_NONE);
  m_calls++;
}
