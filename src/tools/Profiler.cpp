#include "Profiler.hpp"
#include "Logger.hpp"

#if __WIN32__
#include "pdh.h"
#include "psapi.h"
#include "tchar.h"
#include <windows.h>
#endif

Profiler::Profiler() {}

Profiler::~Profiler() {}

void Profiler::update() {
#if __WIN32__
  PROCESS_MEMORY_COUNTERS_EX pmc;
  GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc,
                       sizeof(pmc));
  SIZE_T virtualMemUsedByMe = pmc.WorkingSetSize;
  Logger::log("Virtual Memory Used: " + std::to_string(virtualMemUsedByMe));
#endif
}

void Profiler::print() {}
