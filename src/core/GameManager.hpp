#pragma once 

#include <list>
#include <string>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include "../components/ComponentStore.hpp"
#include "ComponentFactory.hpp"
class GameAsset;
class ISystem;

class GameManager{
  public:
    GameManager();
    ~GameManager() = default;
    void init();
    void start();

    void update(float dt);
    void fixed_update(double tmod);
    void render();
    void dispose();
    void add_dynamic_component(EntityID entity, std::shared_ptr<IComponent> component) {
      component->register_component(this, entity);
    }

    EntityID create_entity() {
      return m_next_entity_id++;
    }

    template<typename T>
    void add_component(EntityID entity, const T& component) {
      auto& store = get_store<T>();
      store.add(entity, component);
    }

    template<typename T>
    T* get_component(EntityID entity) {
        auto& store = get_store<T>();
        return store.get(entity);
    }

    template<typename T>
    void remove_component(EntityID entity) {
        auto& store = get_store<T>();
        store.remove(entity);
    }

    template<typename T>
    std::vector<T*> get_components() {
        auto& store = get_store<T>();
        return store.get_all();
    }

    void add_game_asset(std::unique_ptr<GameAsset> game_asset);
    void add_system(std::unique_ptr<ISystem> system);

    std::vector<GameAsset*> get_game_assets() {
        std::vector<GameAsset*> result;
        for (auto& asset : m_game_assets) {
            result.push_back(asset.get());
        }
        return result;
    }

    std::unique_ptr<ComponentFactory> component_factory;


  private:
    std::vector<std::unique_ptr<GameAsset>> m_game_assets;
    std::vector<std::unique_ptr<ISystem>> m_systems;
    template<typename T>
    ComponentStore<T>& get_store() {
        auto type = std::type_index(typeid(T));
        if (m_component_stores.find(type) == m_component_stores.end()) {
            // Use a custom deleter to properly delete the ComponentStore<T>
            m_component_stores[type] = std::shared_ptr<void>(
                new ComponentStore<T>(),
                [](void* ptr) { delete static_cast<ComponentStore<T>*>(ptr); }
            );
        }
        return *static_cast<ComponentStore<T>*>(m_component_stores[type].get());
    }
    EntityID m_next_entity_id = 0;
    std::unordered_map<std::type_index, std::shared_ptr<void>> m_component_stores;
};
