// include/abslogi.cpp

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
#include "abslogi.hpp"

// Append to namespace
namespace SysCore {
  // Constructor
  AbsLogi :: AbsLogi(uint32_t lidx) {
    
  } // End constructor
  
  // Destructor
  AbsLogi :: ~AbsLogi() {
    
  } // End destructor
} // End namespace appendment