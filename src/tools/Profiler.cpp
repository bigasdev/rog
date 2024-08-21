#include "Profiler.hpp"
#include "Logger.hpp"

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
    Logger::log("RAM Usage: " + std::to_string(mb));
    Logger::log("CPU Used: " + std::to_string(getCurrentValue()));
    Logger::log("GPU Used: " + std::to_string(getGpuUsage()));
#endif
    m_tick_count = 0;
  }
}

void Profiler::print() {}
