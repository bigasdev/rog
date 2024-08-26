#include "Camera.hpp"

#include "SDL_gpu.h"
#include "../tools/Logger.hpp"
#include "../core/Timer.hpp"
#include "../tools/Math.hpp"
#include <cmath>

Camera::Camera(vec2 size) : m_size(size) {
  m_camera = new GPU_Camera{0,0,0,0,3,3,1,1};
  m_pos = vec2(0, 0);
  m_tracked_pos = nullptr;
}

Camera::~Camera() {
  delete m_camera;
}

void Camera::move() {
  if (m_tracked_pos != nullptr) {

    auto spd_x = 0.015*tracking_speed*m_camera->zoom_x;
    auto spd_y = 0.023*tracking_speed*m_camera->zoom_y;
    auto tx = (m_tracked_pos->x)*0.5f + (m_size.x*0.5f);
    auto ty = (m_tracked_pos->y)*0.5f + (m_size.y*0.5f);

    auto dist_x = std::fabs(tx-raw_focus.x);
    Logger::log("dist_x: " + std::to_string(dist_x));
    if(dist_x >= 0.04f * m_size.x){
      dx += (0.8f * dist_x - 0.04f * m_size.x) * spd_x * Timer::get_tmod();
    }

    auto dist_y = std::fabs(ty-raw_focus.y);
    if(dist_y >= 0.10f * m_size.y){
      dy += (0.8f * dist_y - 0.10f * m_size.y) * spd_y * Timer::get_tmod();
    }

    auto frict_x = base_frict - tracking_speed*m_camera->zoom_x*0.027f*base_frict;
    auto frict_y = frict_x;

    raw_focus.x += dx * Timer::get_tmod();
    dx *= Math::pow(frict_x, Timer::get_tmod());
    raw_focus.y += dy * Timer::get_tmod();
    dy *= Math::pow(frict_y, Timer::get_tmod());

    if(clamp_bounds){
      clamped_focus.x = Math::clamp(raw_focus.x, m_size.x * 0.5f, 400 - m_size.x * 0.5f);
      clamped_focus.y = Math::clamp(raw_focus.y, m_size.y * 0.5f, 240 - m_size.y * 0.5f);
    }else{
      clamped_focus = raw_focus;
    }


    m_camera->x = clamped_focus.x;
    m_camera->y = clamped_focus.y;
  }
}

void Camera::update() {
}

bool Camera::is_on_screen(vec2 pos) {
  return pos.x > m_pos.x && pos.x < m_pos.x + m_size.x &&
         pos.y > m_pos.y && pos.y < m_pos.y + m_size.y;
}

void Camera::track_pos(vec2 *pos) {
  m_tracked_pos = pos;
}

void Camera::set_zoom(float zoom) {
  m_camera->zoom_x = zoom;
  m_camera->zoom_y = zoom;
}
