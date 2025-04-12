#pragma once 

#include <list>
#include <memory>
class IComponent;

class GameAsset
{
  public:
    void init();
    void dispose();

    int GUID = 0;
    std::list<std::unique_ptr<IComponent>> components;
};
