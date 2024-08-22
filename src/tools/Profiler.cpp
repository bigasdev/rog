#include "Profiler.hpp"
#include "Logger.hpp"
#include "../core/Timer.hpp"
#include "../renderer/Renderer.hpp"
#include "../core/Engine.hpp"
#include "../res/Res.hpp"
#include "../core/global.hpp"
#include <string>

#if __WIN32__
#include "TCHAR.h"
#include "pdh.h"
#include "psapi.h"
#include <pdh.h>
#include <pdhmsg.h>
#include <windows.h>
#endif

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;
int m_tick_count;

PDH_HQUERY query;
PDH_HCOUNTER counter;

Profiler::Profiler() {
  SYSTEM_INFO sysInfo;
  FILETIME ftime, fsys, fuser;

  GetSystemInfo(&sysInfo);
  numProcessors = sysInfo.dwNumberOfProcessors;

  GetSystemTimeAsFileTime(&ftime);
  memcpy(&lastCPU, &ftime, sizeof(FILETIME));

  self = GetCurrentProcess();
  GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
  memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
  memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));

  PdhOpenQuery(NULL, NULL, &query);
  PdhAddCounter(query, TEXT("\\GPU Engine(*)\\Utilization Percentage"), NULL,
                &counter);
  PdhCollectQueryData(query);
}
double getGpuUsage() {
  PDH_FMT_COUNTERVALUE counterVal;
  PdhCollectQueryData(query);
  PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE, NULL, &counterVal);
  return counterVal.doubleValue;
}
double getCurrentValue() {
  FILETIME ftime, fsys, fuser;
  ULARGE_INTEGER now, sys, user;
  double percent;
  static ULONGLONG lastTime = 0;

  GetSystemTimeAsFileTime(&ftime);
  memcpy(&now, &ftime, sizeof(FILETIME));

  if (lastTime == 0) {
    lastTime = now.QuadPart;
    return 0.0;
  }

  GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
  memcpy(&sys, &fsys, sizeof(FILETIME));
  memcpy(&user, &fuser, sizeof(FILETIME));
  percent = (sys.QuadPart - lastSysCPU.QuadPart) +
            (user.QuadPart - lastUserCPU.QuadPart);
  percent /= (now.QuadPart - lastTime);
  percent /= numProcessors;
  lastTime = now.QuadPart;
  lastCPU = now;
  lastUserCPU = user;
  lastSysCPU = sys;

  return percent * 100;
}

Profiler::~Profiler() {}

void Profiler::update() {
  m_tick_count++;
  if (m_tick_count >= PROFILER_TICK) {
#if __WIN32__
    auto handle = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(handle, (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
    int mb = pmc.PagefileUsage / ((1024 * 1024) * 1.5);
    m_ram_usage = mb;
    m_cpu_usage = getCurrentValue();

    m_base_info.cpu_line_y = (25*((double)m_cpu_usage/m_base_info.max_cpu_usage));
    m_base_info.ram_line_y = (25*((double)m_ram_usage/m_base_info.max_ram_usage));
    m_frames = Timer::get_frame_count();
    m_calls = g_engine->get_renderer()->get_calls();
#endif
    m_tick_count = 0;
  }
}

float get_pos_x(int value){
  return g_engine->get_window_size().x - value;
}

float get_pos_y(int value){
  return g_engine->get_window_size().y - value;
}


void Profiler::draw() {
  g_engine->get_renderer()->draw_rect({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(150)), 100, 40}, {255, 0, 0, 255});
  g_engine->get_renderer()->draw_rect({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(150)), 100, 40}, {255, 0, 0, 65}, true);
  g_engine->get_renderer()->draw_line({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(120)) - m_base_info.cpu_line_y, static_cast<int>(get_pos_x(5)), static_cast<int>(get_pos_y(120)) - m_base_info.cpu_line_y}, {255, 0, 0, 255});
  g_engine->get_renderer()->draw_text({get_pos_x(102), get_pos_y(138)}, (std::to_string(m_frames)).c_str(), g_res->get_font("arial"), {255, 0, 0, 255});
  g_engine->get_renderer()->draw_text({get_pos_x(102), get_pos_y(148)}, (std::to_string(m_cpu_usage) + "%").c_str(), g_res->get_font("arial"), {255, 0, 0, 255});

  g_engine->get_renderer()->draw_rect({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(100)), 100, 40}, {255, 255, 0, 255});
  g_engine->get_renderer()->draw_rect({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(100)), 100, 40}, {255, 255, 0, 65}, true);
  g_engine->get_renderer()->draw_line({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(70)) - m_base_info.cpu_line_y, static_cast<int>(get_pos_x(5)), static_cast<int>(get_pos_y(70)) - m_base_info.cpu_line_y}, {255, 255, 0, 255});
  g_engine->get_renderer()->draw_text({get_pos_x(102), get_pos_y(98)}, (std::to_string(m_calls) + "c/s").c_str(), g_res->get_font("arial"), {255, 255, 0, 255});

  g_engine->get_renderer()->draw_rect({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(50)), 100, 40}, {0, 255, 0, 255});
  g_engine->get_renderer()->draw_rect({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(50)), 100, 40}, {0, 255, 0, 65}, true);
  g_engine->get_renderer()->draw_line({static_cast<int>(get_pos_x(105)), static_cast<int>(get_pos_y(20)) - m_base_info.ram_line_y, static_cast<int>(get_pos_x(5)), static_cast<int>(get_pos_y(20)) - m_base_info.ram_line_y}, {0, 255, 0, 255});
  g_engine->get_renderer()->draw_text({get_pos_x(102), get_pos_y(48)}, (std::to_string(m_ram_usage) + "mb").c_str(), g_res->get_font("arial"), {0, 255, 0, 255});

  g_engine->get_renderer()->draw_text({get_pos_x(80), 2}, ("_DEBUG " + std::to_string(static_cast<int>(Timer::get_fps())) + " fps").c_str(), g_res->get_font("arial"), {0, 255, 0, 255});
}
