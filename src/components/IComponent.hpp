#pragma once 

class IComponent
{
  public:
  virtual ~IComponent() = default;
  int type = 0;
  bool enabled = true;
};
