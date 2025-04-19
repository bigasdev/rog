#include "SpriteSystem.hpp"

#include "../renderer/Camera.hpp"
#include "../renderer/Renderer.hpp"
#include "../core/global.hpp"
#include "../res/Res.hpp"
#include "../components/IComponent.hpp"
#include "../entity/GameAsset.hpp"
#include "../tools/Logger.hpp"
#include "../components/SpriteComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../core/GameManager.hpp"

void SpriteSystem::awake(){
}

void SpriteSystem::start(){

}

void SpriteSystem::update(double dt){
}

void SpriteSystem::fixed_update(double tmod){
}

void SpriteSystem::render(){
  auto sprite_components = g_game_manager->get_components<SpriteComponent>();
  auto transform_components = g_game_manager->get_components<TransformComponent>();

  for(int i = 0;i < sprite_components.size();i++){
    auto spr = sprite_components[i];
    auto transform = transform_components[i];
    if(spr == nullptr || transform == nullptr || !spr->enabled) continue;
    g_renderer->draw(*g_res->get_texture(spr->spr.sheet), spr->spr, transform->pos);
  }
}

void SpriteSystem::dispose(){
}
