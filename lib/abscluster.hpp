// lib/abscluster.hpp
#ifndef _syscore_abscluster_hpp
#define _syscore_abscluster_hpp

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
  // Wrapper around cpuinfo_cluster (processor cluster)
  class AbsCluster {
  private:
  protected:
  public:
    AbsCluster(uint32_t);
    ~AbsCluster();
  }; // End AbsCluster
} // End appendment
#endif