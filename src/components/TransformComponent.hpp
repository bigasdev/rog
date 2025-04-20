#pragma once 
#include "IComponent.hpp"
#include "../tools/Common.hpp"
#include "../core/GameManager.hpp"

class TransformComponent : public IComponent
{
  public:
    ~TransformComponent() override = default;
    void set_variable(const std::string& name, const std::string& type, const std::string& value) override {
        if (name == "pos" && type == "vec2") {
            sscanf(value.c_str(), "{%f, %f}", &pos.x, &pos.y);
        } else if (name == "scale" && type == "vec2") {
            sscanf(value.c_str(), "{%f, %f}", &scale.x, &scale.y);
        } else if (name == "rotation" && type == "float") {
            rotation = std::stof(value);
        } else if (name == "flip_x" && type == "bool") {
            flip_x = (value == "true");
        } else if (name == "flip_y" && type == "bool") {
            flip_y = (value == "true");
        }
    }
    void register_component(GameManager* game_manager, EntityID entity_id) override {
        game_manager->add_component<TransformComponent>(entity_id, *this);
    }

    vec2 pos = {0, 0};
    vec2 scale = {1, 1};
    float rotation = 0.0f;
    bool flip_x = false;
    bool flip_y = false;
};
