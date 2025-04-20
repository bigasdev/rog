#include "ComponentFactory.hpp"
#include "../components/SpriteComponent.hpp"
#include "../components/TransformComponent.hpp"

ComponentFactory::ComponentFactory() {
    register_component("SpriteComponent", []() { return std::make_shared<SpriteComponent>(); });
    register_component("TransformComponent", []() { return std::make_shared<TransformComponent>(); });
}
