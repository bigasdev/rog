#pragma once
#include "SDL_ttf.h"
#ifndef RES_HPP
#define RES_HPP

#include <iostream>
#include <map>

class Res {
public:
  Res();
  ~Res();

  void init();
  void update();

  // loaders
  void load_fonts();
  void load_sounds();

  //getters 
  TTF_Font *get_font(std::string name) { return m_fonts[name]; }

private:
  std::map<std::string, TTF_Font*> m_fonts;
};
#endif
