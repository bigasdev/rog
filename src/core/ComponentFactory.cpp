#include "ComponentFactory.hpp"
#include "../components/SpriteComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/PlayerMoveComponent.hpp"

ComponentFactory::ComponentFactory() {
    register_component("SpriteComponent", []() { return std::make_shared<SpriteComponent>(); });
    register_component("TransformComponent", []() { return std::make_shared<TransformComponent>(); });
    register_component("PlayerMoveComponent", []() { return std::make_shared<PlayerMoveComponent>(); });
}
