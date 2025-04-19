#include "Game.hpp"
#include "../renderer/Camera.hpp"
#include "../tools/Cooldown.hpp"
#include "../core/Engine.hpp"
#include "../core/InputManager.hpp"
#include "../renderer/Renderer.hpp"
#include "../res/Res.hpp"
#include "../core/global.hpp"
#include "../core/Timer.hpp"
#include "../tools/Math.hpp"
#include "../renderer/Sprite.hpp"
#include "../tools/Logger.hpp"
#include "SDL.h"
#include <algorithm>
#include <memory>
#include <string>

#include "../entity/Entity.hpp"

//FIX:: start of the ecs, this will be better created in the future
#include "../core/GameManager.hpp"
#include "../entity/GameAsset.hpp"
#include "../components/IComponent.hpp"
#include "../components/SpriteComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../systems/SpriteSystem.hpp"
#include "../systems/PlayerMoveSystem.hpp"

std::unique_ptr<GameAsset> g_game_asset = std::make_unique<GameAsset>();
std::unique_ptr<SpriteSystem> m_sprite_system = std::make_unique<SpriteSystem>();
std::unique_ptr<PlayerMoveSystem> m_player_move_system = std::make_unique<PlayerMoveSystem>();
std::unique_ptr<SpriteComponent> orc_spr;


bool moving_right = false;
bool moving_left = false;
bool slow_mo = false;

int hero_x = 2;
float timer = 0;

float dx, dy, dwood;
vec2 hero_pos;
vec2 wood_pos = {20, 40};

std::unique_ptr<Entity> hero;
std::unique_ptr<Entity> hp;


Game::Game() {
}

Game::~Game() {
}

void Game::init() {
  m_camera = new Camera(g_engine->get_window_size());
  m_cooldown = new Cooldown();

  g_cooldown = m_cooldown;
  g_camera = m_camera;

  g_input_manager->bind_keyboard(SDLK_e, &moving_right);
  g_input_manager->bind_keyboard(SDLK_q, &moving_left);
  g_input_manager->bind_keyboard(SDLK_SPACE, &slow_mo);

  g_camera->track_pos(&hero_pos);

  hero = std::make_unique<Entity>("bigas", vec2{0, 0});
  hp = std::make_unique<Entity>("health_potion", vec2{0, 50});

  Logger::log("Hero spr sheet : " + hp->spr.sheet);

  //FIX:: ECS TEST 
  g_game_manager = new GameManager();

  //limit test 
  for (int i = 0; i < 10000; i++) {
    auto sprite_component = std::make_unique<SpriteComponent>();
    sprite_component->spr = g_res->get_sprite("bigas");
    auto transform_component = std::make_unique<TransformComponent>();
    transform_component->pos = vec2{static_cast<float>(i * 26), static_cast<float>(80)};
    transform_component->scale = vec2{1, 1};

    g_game_manager->add_component<SpriteComponent>(i + 1, *sprite_component);
    g_game_manager->add_component<TransformComponent>(i + 1, *transform_component);
    g_game_manager->create_entity();
  }

  g_game_asset->init();
  g_game_manager->add_system(std::move(m_sprite_system));
  g_game_manager->add_system(std::move(m_player_move_system));

  g_game_manager->init();
  g_game_manager->start();
}

void Game::fixed_update(double tmod) {
  dx += (g_input_manager->get_raw_axis().x * 17.5) * tmod;
  dy += (g_input_manager->get_raw_axis().y * 17.5) * tmod;

  hero->fixed_update(tmod);

  g_game_manager->fixed_update(tmod);
}

void Game::update(double dt) {
  m_cooldown->update(dt);

  g_game_manager->update(dt);

  hero->dx = dx;
  hero->dy = dy;

  hero->update(dt);
  hp->update(dt);

  if (moving_left)
    m_camera->track_pos(&wood_pos);
  if(moving_right)
    m_camera->track_pos(&hero_pos);

  if(dx > 0){
    hero->spr.dir = 1;
  }else if(dx < 0){
    hero->spr.dir = -1;
  }

  timer += 1*dt;
  if(timer >= .1f){
    hero_x++;
    if(hero_x >= 6){
      hero_x = 2;
    }
    timer = 0;
  }

  if(slow_mo){
    Timer::apply_slow_mo(.1f * dt);
  }
  
}

void Game::post_update(double dt) {
  m_camera->move();
  m_camera->update();
}

void Game::draw_root() {
}

void Game::draw_ent(){
  g_renderer->draw(*g_res->get_texture(hp->spr.sheet), hp->spr, hp->pos);
  g_renderer->draw(*g_res->get_texture(hero->spr.sheet), hero->spr, hero->pos);

  g_game_manager->render();
}
void Game::draw_ui(){

}

void Game::clean() {
}


