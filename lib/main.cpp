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
  
  // Test of the stream version
  /*std::ifstream fd;
  std::string sub;
  std::string name;
  double user, nice, system, idle, iowait, irq, softirq,
    steal, guest, guest_nice;
  double total;
  double avg;
  for (int i = 0; i < 2; i++) {
    fd.open(PROC_FILE);
    while (fd >> name >> user >> nice >> system >> idle >> iowait
      >> irq >> softirq >> steal >> guest >> guest_nice
    ) {
      sub = name.substr(0,3);
      if (sub != "cpu") { break; }
      total = user + nice + system + idle + iowait + irq + softirq
        + steal + guest + guest_nice;
      avg = ((total - idle) / total) * 100;
      std::cout << name << ":\n total: " << total << "\n idle" << idle << "\n";
    }
    fd.close();
    sleep(2);
  }
  std::cout << "\n\n\n";
  // End stream test
  */
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
  SysCore::SysCache *cache = SysCore::SysCache::instance();
  uint packages = cache->count();
  //uint packages = 5;
  std::cout << "There are " << packages
    << " sockets being watched" << "\n";
    
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
  
  //while (true) {
  //  SysCore::SysCache::stat();
  //}
  return 0;
} // End entry point