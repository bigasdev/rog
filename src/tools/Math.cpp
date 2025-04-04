#include "Math.hpp"
#include <iostream>
#include <cmath>

double Math::lerp(double a, double b, double t)
{
  if (t <= 0.5)
    return a + (b - a) * t;
  else
    return b - (b - a) * (1.0 - t);
}

double Math::move_to(double a, double b, double t)
{
  if (a < b)
    return a + t;
  else
    return a;
}

int Math::clamp(int min, int value, int max)
{
  if (value < min)
    return min;
  else if (value > max)
    return max;
  else
    return value;
}

float Math::clamp(float min, float value, float max)
{
  if (value < min)
    return min;
  else if (value > max)
    return max;
  else
    return value;
}

int Math::round(double value)
{
  return (int)(value + 0.5);
}

int Math::floor(double value)
{
  return (int)value;
}

double Math::sign(double value)
{
  if (value > 0)
    return 1;
  else if (value < 0)
    return -1;
  else
    return 0;
}

double Math::abs(double value)
{
  if (value < 0)
    return -value;
  else
    return value;
}

float Math::fabs(float value)
{
  if (value < 0)
    return -value;
  else
    return value;
}

double Math::pow(double base, double exponent)
{
  double result = 1;
  for (int i = 0; i < exponent; i++)
    result *= base;
  return result;
}

double Math::sqrt(double value)
{
  double result = 0;
  for (int i = 0; i < value; i++)
  {
    if (i * i == value)
    {
      std::cout << "Square root of " << value << " is " << i << std::endl;
      result = i;
      break;
    }
  }
  return result;
}

int Math::percentage(int x, int y)
{
  return (x/y);
}

int Math::dist(int a, int b)
{
  return abs(a - b);
}

bool Math::approx(int a, int b, int tolerance)
{
  return a + tolerance > b && a - tolerance < b;
}

int Math::dist_vec(vec2 a, vec2 b)
{
  return dist(a.x, b.x) + dist(a.y, b.y);
}

int Math::mid(int a, int b)
{
  return (a - b) / 2;
}

vec2 Math::mid_vec(vec2 a, vec2 b)
{
  b.x = b.x / 2;
  b.y = b.y / 2;
  return vec2(mid(a.x, b.x), mid(a.y, b.y));
}

void Math::normalize(vec2 &v)
{
  float magnitude = std::sqrt(v.x * v.x + v.y * v.y);
  if (magnitude != 0.0f)
  { // Avoid division by zero
    v.x /= magnitude;
    v.y /= magnitude;
  }
}
