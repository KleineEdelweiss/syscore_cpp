// lib/absproc.hpp
// BACKUP: 2021-Jun-20 @ 03:36:35

#ifndef _syscore_absproc_hpp
#define _syscore_absproc_hpp

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Other libraries needed
#include <map>
#include <string>
#include <tuple>
#include <vector>

// Append AbsProc to SysCore namespace
namespace SysCore {
  // Frequency table entry
  typedef struct {
    uint32_t index; // Index of logical unit on Linux
    uint64_t freq_clus; // Frequency of the cluster
    uint64_t freq_core; // Frequency of the core
  } freq_entry_t;
  
  // Frequency table itself
  typedef std::map<int, freq_entry_t> freq_tab_t;
  
  /*
   * AbsProc is an abstract processor / CPU
   * class to handle accessing of utilization
   * and settings.
   * 
   * This class combines a wrapping of cpuinfo_package,
   * cpuinfo_core, cpuinfo_cluster, and cpuinfo_processor, and
   * it is instantiated from an index number to a socket, which is
   * passed from the SysCache initiator -- it will have obtained
   * indices from a count of packages.
   */
  class AbsProc {
  private:
    // Load components by package number
    bool load_clusters();
    bool load_cores();
    bool load_processors();
    
    // Instance methods and variables
    const cpuinfo_package *pkg;
    
    // Lists of logical processors, clusters, and core on this package
    std::vector<const cpuinfo_processor*> l_units;
    std::vector<const cpuinfo_core*> l_cores;
    std::vector<const cpuinfo_cluster*> l_clus;
    
    // Frequency update table
    freq_tab_t fqtab;
  protected:
    // Fill methods -- attach components to the package
    bool load();
    
    // Update the frequencies of the parts
    bool update_frequencies();
  public:
    AbsProc(uint32_t); // Constructor takes package index
    ~AbsProc(); // Destructor
    
    // Count the number of processors, clusters, or cores
    uint count_procs() const; // Logical processors (hardware threads)
    uint count_cores() const; // Physical cores
    uint count_clusters() const; // Logical processor groups
    
    // Update the data
    bool update();
    
    // Return a copy of the frequency data
    const freq_tab_t frequencies();
    
    // Name of the package
    std::string name() const;
  }; // End AbsProc
} // End namespace appendent
#endif