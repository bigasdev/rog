#include "Camera.hpp"

#include "SDL_gpu.h"
#include "../tools/Logger.hpp"
#include "../core/Timer.hpp"
#include "../tools/Math.hpp"

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
    auto tx = m_tracked_pos->x - 32;
    auto ty = m_tracked_pos->y - 32;

    auto dist_x = Math::fabs(tx - m_pos.x);
    auto dist_y = Math::fabs(ty - m_pos.y);

    dx += (0.8f*dist_x-m_size.x) * spd_x * Timer::get_dt();
    dy += (0.8f*dist_y-m_size.y) * spd_y * Timer::get_dt();

    m_pos.x = dx;
    m_pos.y = dy;

    m_camera->x = m_pos.x;
    m_camera->y = m_pos.y;
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
