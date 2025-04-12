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
    std::vector<T*> get_components_of_type() {
        std::vector<T*> result;
        for (auto& comp : components) {
            if (auto casted = dynamic_cast<T*>(comp.get())) {
                result.push_back(casted);
            }
        }
        return result;
    }
};
