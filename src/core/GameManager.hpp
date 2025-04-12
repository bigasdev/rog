#pragma once 

#include <list>
#include <string>
#include <vector>
#include <memory>

class GameAsset;
class ISystem;

class GameManager{
  public:
    GameManager();
    ~GameManager() = default;
    void init();
    void start();

    void update();
    void fixed_update();
    void render();
    void dispose();

    void add_game_asset(std::unique_ptr<GameAsset> game_asset);
    void add_system(std::unique_ptr<ISystem> system);

    std::vector<GameAsset*> get_game_assets() {
        std::vector<GameAsset*> result;
        for (auto& asset : m_game_assets) {
            result.push_back(asset.get());
        }
        return result;
    }


  private:
    std::vector<std::unique_ptr<GameAsset>> m_game_assets;
    std::vector<std::unique_ptr<ISystem>> m_systems;
};
