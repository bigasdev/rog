#pragma once

#include "SDL_stdinc.h"
struct Rect {
  int x, y, w, h;

  Rect() : x(0), y(0), w(0), h(0) {}
  Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
};

struct Line {
  int x1, y1, x2, y2;

  Line() : x1(0), y1(0), x2(0), y2(0) {}
  Line(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

struct Color {
  Uint8 r, g, b, a;

  Color() : r(0), g(0), b(0), a(0) {}
  Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}
};

struct vec2 {
  float x, y;

  vec2() : x(0), y(0) {}
  vec2(float x, float y) : x(x), y(y) {}
  bool zero() { return x == 0 && y == 0; }
  bool operator==(const vec2 &v) { return x == v.x && y == v.y; }
  bool operator!=(const vec2 &v) { return x != v.x || y != v.y; }
  vec2 operator+(const vec2 &v) { return vec2(x + v.x, y + v.y); }
  vec2 operator-(const vec2 &v) { return vec2(x - v.x, y - v.y); }
  vec2 operator*(const vec2 &v) { return vec2(x * v.x, y * v.y); }
  vec2 operator/(const vec2 &v) { return vec2(x / v.x, y / v.y); }
  vec2 operator*(const float &f) { return vec2(x * f, y * f); }
};

struct vec3 {
  float x, y, z;
};

struct vec2i {
  int x, y;
};

struct vec3i {
  int x, y, z;
};