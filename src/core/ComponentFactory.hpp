#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include "../components/IComponent.hpp"

class ComponentFactory {
public:
    ComponentFactory();
    ~ComponentFactory() = default;
    using Creator = std::function<std::shared_ptr<IComponent>()>;

    void register_component(const std::string& name, Creator creator) {
        creators[name] = creator;
    }

    std::shared_ptr<IComponent> create(const std::string& name) {
        auto it = creators.find(name);
        if (it != creators.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    std::unordered_map<std::string, Creator> creators;
};
