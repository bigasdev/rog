#pragma once 
#include "IComponent.hpp"
#include "../tools/Common.hpp"
#include "../renderer/Sprite.hpp"
#include "../core/GameManager.hpp"

#include <string>

class SpriteComponent : public IComponent
{
  public:
    ~SpriteComponent() override = default;
    void set_variable(const std::string& name, const std::string& type, const std::string& value) override {
        if (name == "name" && type == "std::string") {
          this->name = value;
        }
    }
    void register_component(GameManager* game_manager, EntityID entity_id) override {
        game_manager->add_component<SpriteComponent>(entity_id, *this);
    }

    std::string name = "bigas";
    [[NotSerializable]]Sprite spr;
  private:
};
