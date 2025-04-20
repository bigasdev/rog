#include "GameManager.hpp"
#include "../entity/GameAsset.hpp"

#include "../components/IComponent.hpp"
#include "../systems/ISystem.hpp"

GameManager::GameManager() {
  component_factory = std::make_unique<ComponentFactory>();
}

void GameManager::init() {
  for(auto& system : m_systems) {
    system->awake();
  }
}
void GameManager::start() {
  for(auto& system : m_systems) {
    system->start();
  }
}

void GameManager::update(float dt){
  
  for(auto& system : m_systems) {
    system->update(dt);
  }
}
void GameManager::fixed_update(double tmod){

  for(auto& system : m_systems) {
    system->fixed_update(tmod);
  }
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
