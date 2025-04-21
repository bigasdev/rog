#include "PlayerMoveSystem.hpp"

#include "../core/global.hpp"
#include "../core/GameManager.hpp"
#include "../core/InputManager.hpp"
#include "../components/TransformComponent.hpp"
#include "../tools/Logger.hpp"
#include "../components/PlayerMoveComponent.hpp"



void PlayerMoveSystem::awake(){

}

void PlayerMoveSystem::start(){

}

void PlayerMoveSystem::update(double dt){
  auto player = g_game_manager->get_component<TransformComponent>(PLAYER);
  auto player_move = g_game_manager->get_component<PlayerMoveComponent>(PLAYER);
  if(player == nullptr || player_move == nullptr) return;

  player->pos.x += (player_move->speed * dt) * g_input_manager->get_raw_axis().x;
  player->pos.y += (player_move->speed * dt) * g_input_manager->get_raw_axis().y;
}

void PlayerMoveSystem::fixed_update(double tmod){

}

void PlayerMoveSystem::render(){

}

void PlayerMoveSystem::dispose(){
  
}
