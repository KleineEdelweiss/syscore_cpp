// lib/main.cpp

// Regular libraries
#include <cstdio>
#include <cstdlib>

// Operation libraries
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

// Other
#include <cpuinfo.h>

// More complex libraries
#include <boost/algorithm/string.hpp>

// SysCore
#include "syscore.hpp"

// Defines
#ifndef BUFFSIZE
  #define BUFFSIZE 2^16
#endif

// Entry point
int main(int argc, char **args) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  SysCore::SysCache *cache = SysCore::SysCache::instance();
  uint packages = cache->count();
  std::cout << "There are " << packages
    << " sockets being watched" << "\n";
  sleep(2);
  cache->stat();
  sleep(2);
  cache->stat();
    
  const SysCore::AbsProc *item;
    
  // Read out the info
  for (int i = 0; i < packages; i++) {
    item = &cache->get(i);
    std::string name = item->name();
    std::cout << "Processor at index " << i 
      << " is: " << name << "\n";
    std::cout << "This package contains "
      << item->count_procs() << " logical units, "
      << item->count_cores() << " cores, and "
      << item->count_clusters() << " processing clusters."
      << "\n";
  }
  
  return 0;
} // End entry point