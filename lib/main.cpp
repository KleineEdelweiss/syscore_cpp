// lib/main.cpp

// Regular libraries
#include <cstdio>
#include <cstdlib>

// Operation libraries
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
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

#define PROC_FILE "/proc/stat"

// Entry point
int main(int argc, char **args) {
  /*std::ifstream ifs(PROC_FILE);
  std::map<std::string, std::deque<ulong>> proc_map;
  
  std::deque<std::string> fields;
  std::deque<ulong> data;
  std::string line, key, match;
  
  while (std::getline(ifs, line)) {
    // Check if the line contains data (it should)
    if (line.empty()) { continue; }
    boost::algorithm::split(fields, line, boost::is_any_of("\t\n\r "),
      boost::token_compress_on);
    key = fields.front();
    match = key.substr(0,3);
    if (match == "cpu") {
      if (match.size() == key.size()) { key = std::string("avg"); }
      fields.pop_front(); // Remove the key, now
      while (fields.size() > 0) {
        data.push_back(std::stol(fields.front(), nullptr));
        fields.pop_front();
      }
      proc_map.insert_or_assign(key, data);
      std::cout << "Key is: '" << key << "'" << std::endl;
    }
  }
  std::cout << "The file contains " << proc_map.size()
    << " lines of data" << std::endl;
  */
  uint packages = SysCore::AbsProc::load_units();
  std::cout << "There are " << packages
    << " sockets being watched" << std::endl;
    
  // Read out the info
  for (int i = 0; i < packages; i++) {
    SysCore::AbsProc item = SysCore::AbsProc::get(i);
    std::cout << "Processor at index " << i 
      << " is: " << item.get_name() << std::endl;
  }
  return 0;
} // End entry point