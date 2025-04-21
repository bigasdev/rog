#pragma once 

#include <list>
#include <memory>
#include <vector>
#include "../components/IComponent.hpp"

class GameAsset
{
  public:
    void init();
    void dispose();

    int GUID = 0;
    std::vector<std::unique_ptr<IComponent>> components;

    template<typename T>
    T* get_component_of_type() {
        T* result;
        for (auto& comp : components) {
            if (auto casted = dynamic_cast<T*>(comp.get())) {
                result = casted;
                return result;
            }
        }
        return nullptr;
    }
};
