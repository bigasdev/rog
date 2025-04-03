#include "Entity.hpp"
#include "../core/global.hpp"
#include "../res/Res.hpp"
#include "../tools/Math.hpp"
#include "AffectManager.hpp"
#include "../tools/Cooldown.hpp"
#include "../renderer/Camera.hpp"
#include  "../tools/Logger.hpp"

Entity::Entity() {
}

Entity::Entity(std::string spr_name, vec2 _pos) {
  spr = g_res->get_sprite(spr_name);
  pos = _pos;

  m_cooldown = new Cooldown();
  m_affect_manager = new AffectManager();
}

Entity::~Entity() {
}

void Entity::move_to(vec2 target, float speed) {
  vec2 dir = target - pos;
  Math::normalize(dir);

  dx = dir.x * speed;
  dy = dir.y * speed;
}

Rect Entity::get_collision_box() {
  return Rect(pos.x + spr.spr_x + spr.col_x, pos.y + spr.spr_y + spr.col_y, spr.col_wid * g_camera->get_game_scale(), spr.col_hei * g_camera->get_game_scale());
}

void Entity::update(double dt) {
  m_cooldown->update(dt);
  m_affect_manager->update(dt);

  pos.x += dx;
  pos.y += dy;
}

void Entity::fixed_update(double tmod) {
  dx*=Math::pow(frict_x, tmod);
  dy*=Math::pow(frict_y, tmod);

}


