#include "SpriteComponent.hpp"
#include "../tools/Logger.hpp"
#include "../renderer/Camera.hpp"
#include "../renderer/Renderer.hpp"
#include "../res/Res.hpp"
#include "../core/global.hpp"


SpriteComponent::SpriteComponent(const std::string& sprite, const vec2& _pos) {
  spr = g_res->get_sprite(sprite);
  pos = _pos;
}




































