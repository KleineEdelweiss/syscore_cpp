// lib/absproc.cpp
// BACKUP: 2021-Jun-20 @ 03:36:35

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
#include <map>
#include <string>
#include <tuple>
#include <vector>

// This header
#include "absproc.hpp"

namespace SysCore {
  // Static methods
  
  // Add the clusters
  bool AbsProc :: load_clusters() {
    // Start and end of cluster list
    int start = pkg->cluster_start;
    int cnt = pkg->cluster_count;
    int end = start + cnt; // Will actually be one more than, so use <
    
    // Add each cluster
    for (int i = start; i < end; i++) {
      //l_clus.push_back(AbsCluster(i));
      const cpuinfo_cluster *item = cpuinfo_get_cluster(i);
      // Check to ensure not intermingled data
      if (item->package == pkg) {
        l_clus.push_back(item);
      }
    }
    return true;
  } // End cluster insert
  
  // Add the physical cores
  bool AbsProc :: load_cores() {
    // Start and end of core list
    int start = pkg->core_start;
    int cnt = pkg->core_count;
    int end = start + cnt; // Will actually be one more than, so use <
    
    // Add each core
    for (int i = start; i < end; i++) {
      //l_cores.push_back(AbsCore(i));
      const cpuinfo_core *item = cpuinfo_get_core(i);
      // Check to ensure not intermingled data
      if (item->package == pkg) {
        l_cores.push_back(item);
      }
    }
    return true;
  } // End core insert
  
  // Add the logical processors
  bool AbsProc :: load_processors() {
    // Start and end of logical processor list
    int start = pkg->processor_start;
    int cnt = pkg->processor_count;
    int end = start + cnt; // Will actually be one more than, so use <
    
    // Add each logical unit
    for (int i = start; i < end; i++) {
      //AbsLogi unit = AbsLogi(i);
      //unit.mem_of_package(pkg);
      const cpuinfo_processor *item = cpuinfo_get_processor(i);
      // Check to ensure not intermingled data
      if (item->package == pkg) {
        l_units.push_back(item);
      }
    }
    return true;
  } // End logical processor insert
  
  /*
   * Constructor -- takes a cpuinfo_package pointer
   * and converts it into this class, loading the
   * remaining necessary data about the CPU package.
   */
  AbsProc :: AbsProc(uint32_t socket) {
    // Store the pointer to the package
    pkg = cpuinfo_get_package(socket);
    load(); // Load the remaining parts
  } // End constructor
  
  // Destructor
  AbsProc :: ~AbsProc() {
    // The library seems to handle cleanup and crashes trying
    // to delete any pointers to the internal structs. So just
    // set the pointer NULL
    pkg = NULL;
    
    // Clear all the vectors
    l_units.clear();
    l_cores.clear();
    l_clus.clear();
    
    // Clear the frequency update table
    fqtab.clear();
  } // End destructor
  
  // Return the name of the processor
  std::string AbsProc :: name() const {
    return std::string(pkg->name);
  } // End name getter
  
  // Load in all the parts of the instance
  bool AbsProc :: load() {
    // First, load in all the logical units
    return
      load_processors()
      && load_cores()
      && load_clusters()
      && update();
  } // End loading procedure
  
  // Count the units attached
  uint AbsProc :: count_procs() const { return l_units.size(); }
  uint AbsProc :: count_cores() const { return l_cores.size(); }
  uint AbsProc :: count_clusters() const { return l_clus.size(); }
  
  // Update the data
  bool AbsProc :: update() {
    return update_frequencies();
  } // End update method
  
  /* 
   * Get the frequencies by logical processor. This maps
   * the logical processing unit's Linux ID to a tuple of
   * <cluster_freq, core_freq>
   */
  bool AbsProc :: update_frequencies() {
    // Loop over each processor
    for (auto lproc : l_units) {
      // Load the data
      int procid = lproc->linux_id;
      auto it = fqtab.find(procid);
      
      // Decide whether to update or add the frequency data
      /*if (it == fqtab.end()) {
        // If it is not there, generate the struct
        freq_entry_t entry;
        entry.index = procid;
        entry.freq_clus = lproc->cluster->frequency;
        entry.freq_core = lproc->core->frequency;
        
        std::cout << "Frequencies: " << lproc->cluster->frequency
          << " " << lproc->core->frequency << std::endl;
        
        // Add the entry to the table
        fqtab.emplace(procid, entry);
      } else {
        // Otherwise, just update the entry
        it->second.freq_clus = lproc->cluster->frequency;
        it->second.freq_core = lproc->core->frequency;
      }*/
    }
    return true;
  } // End update frequency by processor
  
  // Return the frequency data for the processors
  const freq_tab_t AbsProc :: frequencies() {
    return fqtab;
  } // End frequencies getter
} // End namespace appendment