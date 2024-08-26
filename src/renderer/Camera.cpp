#include "Camera.hpp"

#include "SDL_gpu.h"
#include "../tools/Logger.hpp"

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

    m_ref_pos = *m_tracked_pos;
    m_ref_pos.x += 32;
    m_ref_pos.y += 32;

    m_pos = m_ref_pos - (m_size / 2);
    Logger::log(std::to_string(m_pos.x) + " " + std::to_string(m_pos.y));
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
