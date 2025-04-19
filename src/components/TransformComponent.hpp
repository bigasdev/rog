#pragma once 
#include "IComponent.hpp"
#include "../tools/Common.hpp"

class TransformComponent : public IComponent
{
  public:
    ~TransformComponent() override = default;

    vec2 pos = {0, 0};
    vec2 scale = {1, 1};
    float rotation = 0.0f;
    bool flip_x = false;
    bool flip_y = false;
};
