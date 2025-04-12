#pragma once 

#include <list>
#include <memory>

class GameAsset;
class ISystem;

class GameManager{
  public:
    GameManager();
    ~GameManager() = default;
    void init();

    void dispose();

    void add_game_asset(std::unique_ptr<GameAsset> game_asset);
    void add_system(std::unique_ptr<ISystem> system);

  private:
    std::list<std::unique_ptr<GameAsset>> m_game_assets;
    std::list<std::unique_ptr<ISystem>> m_systems;
};
