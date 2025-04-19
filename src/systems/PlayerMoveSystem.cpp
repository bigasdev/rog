#include "PlayerMoveSystem.hpp"

#include "../core/global.hpp"
#include "../core/GameManager.hpp"
#include "../components/TransformComponent.hpp"



void PlayerMoveSystem::awake(){

}

void PlayerMoveSystem::start(){

}

void PlayerMoveSystem::update(double dt){
  auto player = g_game_manager->get_component<TransformComponent>(PLAYER);
  if(player == nullptr) return;

  player->pos.x += 15 * dt;
  player->pos.y += 5 * dt;
}

void PlayerMoveSystem::fixed_update(double tmod){

}

void PlayerMoveSystem::render(){

}

void PlayerMoveSystem::dispose(){
  
}
