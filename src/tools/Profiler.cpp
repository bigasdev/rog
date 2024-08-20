#include "Profiler.hpp"
#include "Logger.hpp"

#if __WIN32__
#include "TCHAR.h"
#include "pdh.h"
#include "psapi.h"
#include <windows.h>
#endif

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

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
}
double getCurrentValue(){
    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) +
        (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent * 100;
}

Profiler::~Profiler() {}

void Profiler::update() {
#if __WIN32__
  MEMORYSTATUSEX memInfo;
  memInfo.dwLength = sizeof(MEMORYSTATUSEX);
  GlobalMemoryStatusEx(&memInfo);
  DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
  Logger::log("RAM Used: " + std::to_string(physMemUsed));
  Logger::log("CPU Used: " + std::to_string(getCurrentValue()));
#endif
}

void Profiler::print() {}
