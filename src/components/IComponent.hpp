#pragma once 

struct IComponent
{
  virtual ~IComponent() = default;
  bool enabled = true;
};
