// include/abscore.cpp

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
#include "abscore.hpp"

// Append to SysCore namespace
namespace SysCore {
  // Constructor builds core from index
  AbsCore :: AbsCore(uint32_t) {
    
  } // End constructor
  
  // Destructor
  AbsCore :: ~AbsCore() {
    
  } // End destructor
} // End namespace appendment