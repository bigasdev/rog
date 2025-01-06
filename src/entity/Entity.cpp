#include "Entity.hpp"
#include "../core/global.hpp"
#include "../res/Res.hpp"
#include "../tools/Math.hpp"
#include "AffectManager.hpp"
#include "../tools/Cooldown.hpp"

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


