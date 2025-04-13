#pragma once 
#include "IComponent.hpp"
#include "../tools/Common.hpp"
#include "../renderer/Sprite.hpp"

#include <string>

class SpriteComponent : public IComponent
{
  public:
    SpriteComponent(const std::string& sprite);
    ~SpriteComponent() override = default;

    int type = 1;
    Sprite spr;
  private:
};
