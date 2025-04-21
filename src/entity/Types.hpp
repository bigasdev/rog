#pragma once

#include <cstdint>
#include <string>
#include <vector>
#define PLAYER 0

using EntityID = uint32_t;

struct VariableData{
  std::string name;
  std::string type;
  std::string val;
};

struct ComponentData{
  std::string name;
  bool active = false;
  std::vector<VariableData> variables;
};

struct Prefab {
  std::string name;
  std::vector<ComponentData> components;

  ComponentData* get_component(const std::string& name) {
    for (auto& component : components) {
      if (component.name == name) {
        return &component;
      }
    }
    return nullptr;
  }
};
