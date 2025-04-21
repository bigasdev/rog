#pragma once 
#include "IComponent.hpp"
#include "../tools/Common.hpp"
#include "../core/GameManager.hpp"

class PlayerMoveComponent : public IComponent
{
  public:
    ~PlayerMoveComponent() override = default;
    void set_variable(const std::string& name, const std::string& type, const std::string& value) override {
        if (name == "speed" && type == "float") {
            speed = std::stof(value);
        }
    }
    void register_component(GameManager* game_manager, EntityID entity_id) override {
        game_manager->add_component<PlayerMoveComponent>(entity_id, *this);
    }

    float speed = 0;
};
