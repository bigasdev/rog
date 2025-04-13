#pragma once 

class IComponent
{
  public:
  virtual ~IComponent() = default;
  bool enabled = true;
};
