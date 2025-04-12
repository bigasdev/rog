#pragma once 

#include <list>
#include <memory>
class IComponent;

class ISystem
{
  public:
    virtual void awake() = 0;
    virtual void start() = 0;
    virtual void update(double dt) = 0;
    virtual void fixed_update(double tmod) = 0;
    virtual void render() = 0;
    virtual void dispose() = 0;

    std::list<std::unique_ptr<IComponent>> m_components;
};
