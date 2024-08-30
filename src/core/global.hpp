#pragma once 
#ifndef GLOBAL_HPP
#define GLOBAL_HPP

class Engine;
class Res;
class SoundManager;
class Camera;
class InputManager;

extern Engine* g_engine;
extern Res* g_res;
extern Camera* g_camera;
extern SoundManager* g_sound_manager;
extern InputManager* g_input_manager;

extern bool g_controller_connected;

#endif
