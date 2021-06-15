// lib/absproc.cpp

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
#include <mutex>
#include <string>
#include <vector>

// This header
#include "absproc.hpp" 
//#include "syscore.hpp"

namespace SysCore {
  // Static variables
  std::vector<AbsProc> AbsProc :: packages;
  
  // Static methods
  
  // Add the clusters
  bool AbsProc :: load_clusters(uint32_t idx, std::vector<AbsCluster> *cl) {
    return true;
  } // End cluster insert
  
  // Add the physical cores
  bool AbsProc :: load_cores(uint32_t idx, std::vector<AbsCore> *cr) {
    return true;
  } // End core insert
  
  // Add the logical processors
  bool AbsProc :: load_processors(uint32_t idx, std::vector<AbsLogi> *lg) {
    std::cerr << "Logical units stored? " << lg->size() << std::endl;
    std::cerr << "Logical units to store? " << cpuinfo_get_processors_count() << std::endl;
    return true;
  } // End logical processor insert
  
  // Return a constant processor
  AbsProc const AbsProc :: get(uint idx) {
    if (idx < packages.size()) {
      const AbsProc pkg = packages.at(idx);
      return(pkg);
    } else {
      throw("No packages, yet; please load them in.");
    }
  } // End getter for a specific processor
  
  /*
   * Initialize the library -- this should be
   * checked for all components.
   *
   * If the library is initialized, just return true.
   */
  bool AbsProc :: lib_init() {
    // Initializing multiple times doesn't seem
    // to cause any issues.
    // Return if the library can be initialized.
    return cpuinfo_initialize();
  } // End library initialization
  
  // Fatal error message for if the library could not be initialized.
  // Aborts program execution.
  void AbsProc :: init_fatal() {
    std::cerr << "::FATAL ERROR (SysCore):: Could not initialize 'cpuinfo'"
      << std::endl << "Aborting" << std::endl;
    abort();
  } // End fatal error message and abort
  
  /* 
   * De-initialize the library and clear all the
   * existing static structs stored in the vectors.
   */
  void AbsProc :: lib_deinit() {
    //cpuinfo_deinitialize();
    // Only de-init, if there's no packages left, when called.
    if (packages.size() < 1) {
      // Clean up the resources
      packages.clear();
      lib_deinit();
    }
  } // End de-init method
  
  /*
   * Populate the vector of processors.
   * This will first try to init the library.
   * 
   * It returns a count of the number of processors.
   */
  uint AbsProc :: load_units() {
    if (!lib_init()) { init_fatal(); }
    else {
      // Fill in the packages
      for (int i = 0; i < cpuinfo_get_packages_count(); i++) {
        AbsProc new_proc = AbsProc(cpuinfo_get_package(i));
        packages.push_back(new_proc);
      }
    }
    return count_units();
  } // End processor loader
  
  // Count of the packages list
  uint AbsProc :: count_units() {
    if (!lib_init()) { init_fatal(); }
    return packages.size();
  } // End package count
  
  /*
   * Constructor -- takes a cpuinfo_package pointer
   * and converts it into this class, loading the
   * remaining necessary data about the CPU package.
   */
  AbsProc :: AbsProc(const cpuinfo_package *pack) {
    if (lib_init()) {
      // Store the name
      name = std::string(pack->name);
      // Store the logical unit limits
      logi_start = pack->processor_start;
      logi_cnt = pack->processor_count;
      // Store the core limits
      core_start = pack->core_start;
      core_cnt = pack->core_count;
      // Store the cluster limits
      clust_start = pack->cluster_start;
      clust_cnt = pack->cluster_count;
      
      // Debug...
      std::cerr << "The first logical unit of " << logi_cnt
        << " is at: " << logi_start
        << std::endl << "The first core of " << core_cnt
        << " is at: " << core_start
        << std::endl << "The first cluster of " << clust_cnt
        << " is at: " << clust_start
        << std::endl;
      // /Debug
      load(); // Load the remaining parts
    } else { init_fatal(); }
  } // End constructor
  
  // Destructor
  AbsProc :: ~AbsProc() {
    
  } // End destructor
  
  // Return the name of the processor
  std::string AbsProc :: get_name() {
    return name;
  } // End name getter
  
  // Load in all the parts of the instance
  bool AbsProc :: load() {
    // Fist, load in all the logical units
    bool logck, corck, clusck;
    logck = load_processors(logi_start, &l_units);
    corck = load_cores(core_start, &l_cores);
    clusck = load_clusters(clust_start, &l_clus);
    return logck && corck && clusck;
  } // End loading procedure
} // End namespace appendment