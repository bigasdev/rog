#pragma once 
#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "../tools/Common.hpp"

struct Sprite{
  //positions 
  float spr_x, spr_y;

  //scale
  float wid, hei;
  float scale_x = 1.0f, scale_y = 1.0f;
  float squash_x = 1.0f, squash_y = 1.0f;

  //rotation 
  float angle = 0;

  //visibility
  int z_order = 0;
  int dir = 1;
  int alpha = 255;
  bool visible = true;

  //shaders 
  int shader_id = 0;
  int shader_block_id = 0;
};

#endif
