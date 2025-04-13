#include "TransformComponent.hpp"

TransformComponent::TransformComponent(vec2 _pos, vec2 _scale, float _rotation) : IComponent() {
  pos = _pos;
  scale = _scale;
  rotation = _rotation;
}
