// lib/abscore.hpp
#ifndef _syscore_abscore_hpp
#define _syscore_abscore_hpp

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Other libraries needed
#include <string>
#include <vector>

// Append to SysCore namespace
namespace SysCore {
  // Wrapper around cpuinfo_core (processor physical core)
  class AbsCore {
  private:
  protected:
  public:
    AbsCore(uint32_t);
    ~AbsCore();
  }; // End AbsCore
} // End appendment
#endif