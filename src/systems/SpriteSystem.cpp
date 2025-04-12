#include "SpriteSystem.hpp"

#include "../renderer/Camera.hpp"
#include "../renderer/Renderer.hpp"
#include "../core/global.hpp"
#include "../res/Res.hpp"
#include "../components/IComponent.hpp"
#include "../entity/GameAsset.hpp"
#include "../components/SpriteComponent.hpp"
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
  for(auto& game_asset : g_game_manager->get_game_assets()){
    auto components = game_asset->get_components_of_type<SpriteComponent>();
    for(auto& component : components){
      auto sprite_component = static_cast<SpriteComponent*>(component);
      g_renderer->draw(*g_res->get_texture(sprite_component->spr.sheet), sprite_component->spr, sprite_component->pos);
    }
  }
}

void SpriteSystem::dispose(){
}
