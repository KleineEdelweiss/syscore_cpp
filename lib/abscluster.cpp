// include/abscluster.cpp

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Other libraries needed
#include <csignal>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

// This header
#include "abscluster.hpp"

// Append to namespace
namespace SysCore {
  // Constructor
  AbsCluster :: AbsCluster(uint32_t cidx) {
    
  } // End constructor
  
  // Destructor
  AbsCluster :: ~AbsCluster() {
    
  } // End destructor
} // End namespace appendment