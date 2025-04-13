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
  for(auto& game_asset : g_game_manager->get_game_assets()){
    auto spr = game_asset->get_component_of_type<SpriteComponent>();
    auto transform = game_asset->get_component_of_type<TransformComponent>();
    if(spr == nullptr || transform == nullptr || !spr->enabled) continue;
    g_renderer->draw(*g_res->get_texture(spr->spr.sheet), spr->spr, transform->pos);
  }
}

void SpriteSystem::dispose(){
}
