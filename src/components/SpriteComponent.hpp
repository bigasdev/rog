#pragma once 
#include "IComponent.hpp"
#include "../tools/Common.hpp"
#include "../renderer/Sprite.hpp"

#include <string>

class SpriteComponent : public IComponent
{
  public:
    ~SpriteComponent() override = default;

    std::string name = "bigas";
    Sprite spr;
  private:
};
