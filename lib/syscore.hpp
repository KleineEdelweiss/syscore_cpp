// lib/syscore.hpp

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Other libraries needed
#include <string>
#include <vector>

class AbstractProcessor {
private:
  // Store a count of all the active instances
  // of the AbstractProcessor
  static int count;
  
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
  int curr_count(); // INSTANCE count of logical processors
  std::string curr_name(); // Get name of INSTANCE package
};