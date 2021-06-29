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
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

// Local includes
#include "absproc.hpp"

#define PROC_FILE "/proc/stat"
#define PROC_FMT "%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu"

// Namespace to store system devices
namespace SysCore {
  /* 
   * PIMPL class to manage the operations
   * without direct access to the deeper backend.
   */
  class SysCache {
  private:
    // Library
    static bool lib_init();
    static void lib_deinit();
    static void init_fatal();
    
    // Singleton instance to access the data
    static SysCache *cache;
    
    // List of packages
    std::vector<AbsProc> packages;
    
    // Core ID mapped to (TOTAL, IDLE, PERCENTAGE) of last value
    typedef std::tuple<long, long, float> usage_t;
    std::map<std::string, usage_t> prev_data;
    
    // Maximum line to read
    static int end_of_cores;
    
    // Private constructor and destructor
    SysCache();
    ~SysCache();
    
    // Private load methods
    bool load();
    bool load_proc();
  protected:
  public:
    // Return the singleton instance
    static SysCache *instance();
    // Get a count of loaded packages
    uint count();
    // Retrieve a pointer to a processor package
    const AbsProc& get(uint);
    // Read the stat file
    bool stat();
    // Update the cache data
    bool update();
  };
} // End SysCore namespace
#endif