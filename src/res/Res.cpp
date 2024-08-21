#include "Res.hpp"
#include "../tools/Reader.hpp"
#include "../core/global.hpp"
#include "../core/SoundManager.hpp"

#include "../tools/Logger.hpp"

Res::Res()
{
}

Res::~Res()
{
}

void Res::init()
{
  load_fonts();
  load_sounds();
}

void Res::load_fonts(){
  auto files = Reader::read_file("res/font");

  for (auto file : files)
  {
    std::string path = file;
    std::string file_name = path.substr(path.find_last_of("/\\") + 1);
    file_name = file_name.substr(0, file_name.find_last_of("."));
    Logger::log("Loading font: " + file_name);
    TTF_Font* font = TTF_OpenFont(path.c_str(), 8);
    if (font == nullptr)
    {
      Logger::error("Failed to load font: " + path);
    }
    else
    {
      Logger::log("Loaded font: " + path);
      m_fonts.insert(std::make_pair(file_name, font));
    }
  }
}

void Res::load_sounds(){
  auto sounds = Reader::get_extension_files("res/sounds", ".wav");

  for (auto sound : sounds)
  {
    std::string path = sound;
    std::string file_name = path.substr(path.find_last_of("/\\") + 1);
    file_name = file_name.substr(0, file_name.find_last_of("."));
    Logger::log("Loading sound: " + file_name);
    g_sound_manager->load_sound(path.c_str(), file_name);
  }
}

void Res::update()
{
#if _DEBUG
#endif
}
