// lib/syscore.cpp

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Other libraries needed
#include <csignal>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

// This header
#include "syscore.hpp"

// Local includes
#include "absproc.hpp"

// SysCore namespace
namespace SysCore {
  // Register a class that is supposed to store static
  // references to the library.
  /*bool reg_class(std::type_info obj) {
    int prev = reg_objects.size();
    reg_objects.insert(obj);
    return(prev < reg_objects.size());
  }*/ // End class registration
  
  // Static variables
  // The cache instance
  SysCache* SysCache :: cache = 0;
  
  // Max cores
  int SysCache :: end_of_cores = 0;
  
  // Static methods
  /*
   * Initialize the library -- this should be
   * checked for all components.
   *
   * If the library is initialized, just return true.
   */
  bool SysCache :: lib_init() {
    // Initializing multiple times doesn't seem
    // to cause any issues.
    // Return if the library can be initialized.
    return cpuinfo_initialize();
  } // End library initialization
  
  // Fatal error message for if the library could not be initialized.
  // Aborts program execution.
  void SysCache :: init_fatal() {
    std::cerr << "::FATAL ERROR (SysCache):: Could not initialize 'cpuinfo'"
      << std::endl << "Aborting" << std::endl;
    abort();
  } // End fatal error message and abort
  
  /* 
   * De-initialize the library and clear all the
   * existing static structs stored in the vectors.
   */
  void SysCache :: lib_deinit() {
    // Only de-init, if there's no packages left, when called.
    if (cache->packages.size() < 1) {
      // Clean up the resources
      cache->packages.clear();
      cpuinfo_deinitialize();
    }
  } // End de-init method
  
  // Constructor -- initialize the object as a Singleton
  SysCache :: SysCache() {
    if (lib_init()) {
      load();
    } else { init_fatal(); }
  } // End SysCache constructor
  
  // Destructor
  SysCache :: ~SysCache() {
    //cache->packages.clear();
    //delete packages;
    //packages = NULL;
  } // Destructor
  
  /*
   * Return the instance, if one exists.
   * If it does not, create it and return it.
   */
  SysCache* SysCache :: instance() {
    // Create, if not exists
    //std::cout << "Getting instance" << std::endl;
    if (!cache) {
      //std::cout << "Instance was previously NULL" << std::endl;
      cache = new SysCache;
      //std::cout << "New instance created" << std::endl;
    }
    //std::cout << "Returning cache" << std::endl;
    return cache; // Return it back
  } // End instance retriever
  
  /*
   * Private load method initializes the cache
   * with the abstract processor units.
   */
  bool SysCache :: load() {
    int nr_packs = cpuinfo_get_packages_count();
    // If there are not detected packages (should not happen)
    if (nr_packs < 1) {
      throw("::ERROR SysCache:: Failed to load any packages. This may " \
        "be due to unsupported hardware. This library will not abort, " \
        "however, but it cannot report on the CPU packages on your system.\n");
      return false;
    }
    // Add each package to the instance's storage vector
    for (int i = 0; i < nr_packs; i++) {
      AbsProc item = AbsProc(i);
      packages.push_back(item);
    }
    load_proc();
    return true;
  } // End load method
  
  // Return a constant processor
  const AbsProc& SysCache :: get(uint idx) {
    SysCache *c = instance();
    // Check if cache could be retrieved
    if (!c) {
      throw("::FATAL ERROR (SysCache):: Cannot retrieve cache! Aborting.");
      abort();
    }
    
    // Return the requested package
    if (idx < c->packages.size()) {
      return(c->packages.at(idx));
    } else {
      throw("::ERROR (SysCache):: Package requested is out of range.");
    }
  } // End getter for a specific processor
  
  // Count of the packages cached
  uint SysCache :: count() {
    SysCache *c = instance();
    //return -1;
    return c->packages.size();
  } // End package count
  
  /* 
   * Load the proc file data.
   * 
   * On load, this will store the std::string name of the core in
   * prev_data, as a key. The key will be attached to an std::tuple
   * of LONG values. These longs represent the last state read in,
   * and they consist of (LAST_TOTAL, LAST_IDLE, LAST_PERCENTAGE).
   * 
   * During subsequent reads, the process will follow as thus:
   * 1) Read the previous values
   * 2) Read in the new values stream
   * 3) Generate the current usage levels
   * 4) Store the usage levels in the cache
   * 5) Update the previous values to the new values
   */
  bool SysCache :: load_proc() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::cout << std::fixed << std::setprecision(0);
    
    std::ifstream fd;
    std::string sub;
    std::string name;
    double user, nice, system, idle, iowait, irq, softirq,
      steal, guest, guest_nice;
    double total;
    double avg;
    int count = 0;
    fd.open(PROC_FILE);
    while (fd >> name >> user >> nice >> system >> idle >> iowait
      >> irq >> softirq >> steal >> guest >> guest_nice
    ) {
      sub = name.substr(0,3);
      if (sub != "cpu") { break; }
      total = user + nice + system + idle + iowait + irq + softirq
        + steal + guest + guest_nice;
      avg = ((total - idle) / total) * 100;
      std::cout << "ROW : " << name << " " << user << " " << nice << " "
        << system << " " << idle << " " << iowait << " " << irq << " "
        << softirq << " " << steal << " " << guest << " " << guest_nice << "\n"
        << " total: " << total << "\n---\n";
      
      //float perc = ;
      usage_t data = std::make_tuple(total, idle, 0.0);
      prev_data.insert_or_assign(name, data);
      count++;
    }
    fd.close();
    std::cout << "Total lines with core data in proc file: " << count << "\n";
    end_of_cores = count;
    return true;
  } // End proc file loader
  
  // Update the cache data
  bool SysCache :: update() {
    // Count the cores in proc file
    if (end_of_cores < 1) {
      
    }
    
    return true;
  } // End update method
  
  // Read in the stat file and update the packages
  bool SysCache :: stat() {
    SysCache *c = instance();
    //load_proc();
    return true;
  } // End stat reader
} // End SysCore namespace