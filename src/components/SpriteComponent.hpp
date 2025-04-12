#pragma once 
#include "IComponent.hpp"
#include "../tools/Common.hpp"
#include "../renderer/Sprite.hpp"

#include <string>

class SpriteComponent : public IComponent
{
  public:
    SpriteComponent(const std::string& sprite, const vec2& _pos);
    ~SpriteComponent()  = default;

    int type = 1;
    Sprite spr;
    vec2 pos;
  private:
};
