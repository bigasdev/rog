#pragma once 
#include "IComponent.hpp"

#include "../tools/Common.hpp"

class TransformComponent : public IComponent
{
  public:
    TransformComponent() = default;
    TransformComponent(vec2 _pos, vec2 _scale, float _rotation);
    ~TransformComponent() override = default;

    vec2 pos;
    vec2 scale;
    float rotation;
};
