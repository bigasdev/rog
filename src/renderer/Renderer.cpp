#include "Renderer.hpp"
#include "SDL_gpu.h"

Renderer::Renderer(GPU_Target *gpu) : m_gpu(gpu) {}

Renderer::~Renderer() {}

void Renderer::draw_rect(Rect rect, Color color) {
  GPU_Rectangle(m_gpu, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h,
                {color.r, color.g, color.b, color.a});
}

void Renderer::draw_line(Line line, Color color) {
  GPU_Line(m_gpu, line.x1, line.y1, line.x2, line.y2,
           {color.r, color.g, color.b, color.a});
}

void Renderer::draw_text(vec2 pos, const char *text, TTF_Font *font,
                         Color color, int size, int width) {
  SDL_Surface *surfaceMessage =
      TTF_RenderText_Blended_Wrapped(font, text, {color.r, color.g, color.b, color.a}, width);
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
}