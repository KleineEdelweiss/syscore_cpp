// lib/abslogi.hpp
#ifndef _syscore_abslogi_hpp
#define _syscore_abslogi_hpp

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Append to SysCore namespace
namespace SysCore {
  // Wrapper around cpuinfo_processor (logical processor)
  class AbsLogi {
  private:
    
  protected:
  public:
    AbsLogi(uint32_t);
    ~AbsLogi();
  }; // End AbsLogi
} // End appendment
#endif