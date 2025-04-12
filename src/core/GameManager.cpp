#include "GameManager.hpp"
#include "../entity/GameAsset.hpp"

#include "../components/IComponent.hpp"
#include "../systems/ISystem.hpp"

GameManager::GameManager() {
}

void GameManager::init() {
}
void GameManager::start() {
}

void GameManager::update(){

}
void GameManager::fixed_update(){

}
void GameManager::render(){
  for(auto& system : m_systems) {
    system->render();
  }

}

void GameManager::dispose() {
}

void GameManager::add_game_asset(std::unique_ptr<GameAsset> game_asset) {
    m_game_assets.push_back(std::move(game_asset));
}

void GameManager::add_system(std::unique_ptr<ISystem> system) {
    m_systems.push_back(std::move(system));
}
