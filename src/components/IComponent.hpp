#pragma once 

#include <string>
#include "../entity/Types.hpp"

class GameManager;

struct IComponent
{
  virtual ~IComponent() = default;
  bool enabled = true;

  //this will ensure that we can add the variables depending on the rog-editor
  virtual void set_variable(const std::string& name, const std::string& type, const std::string& value) = 0;
  //dynamic load from the editor
  virtual void register_component(GameManager* game_manager, EntityID entity_id) = 0;
};
