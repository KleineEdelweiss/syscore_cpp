// lib/syscore.hpp
#ifndef _syscore_base_hpp
#define _syscore_base_hpp

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Other libraries needed
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

// Local includes
#include "absproc.hpp"

// Namespace to store system devices
namespace SysCore {
  // Store only the active items
  namespace {
    //std::vector<AbsProc> packages;
    //std::set<std::type_info> reg_objects;
  } // End hidden namespace
  
  // Methods
  //bool reg_class(std::type_info);
} // End SysCore namespace
/*
class AbstractProcessor {
private:
  // Store a count of all the active instances
  // of the AbstractProcessor
  static int watchers;
  
  // Library state
  static bool lib_state;
  
  // Holders for the processor structs
  static std::vector<const cpuinfo_package *> packages;
  
  // Private parts for each package
  const cpuinfo_package *pkg; // The INSTANCE package
  //std::vector<cpuinfo_cluster *> clusters;
  //std::vector<cpuinfo_core *> cores;
  std::vector<const cpuinfo_processor *> processors;

public:
  // Static methods
  static bool lib_initialize(); // Init library
  static void lib_deinitialize(); // De-init library
  static size_t count_pkgs(); // Count total number of packages
  static void init_fatal(); // Fatal error print and abort
  
  // Resource allocation
  AbstractProcessor(); // Constructor
  ~AbstractProcessor(); // Destructor
  
  // Methods
  int load_pkg(int); // Load a specific package into INSTANCE
  int load_procs(); // Load a specific package into INSTANCE
  int curr_count(); // INSTANCE count of logical processors
  std::string curr_name(); // Get name of INSTANCE package
};*/
#endif