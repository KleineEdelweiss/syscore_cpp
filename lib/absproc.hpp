// lib/absproc.hpp
#ifndef _syscore_absproc_hpp
#define _syscore_absproc_hpp

// Core libraries
#include <proc/procps.h>
#include <proc/readproc.h>
#include <proc/sysinfo.h>
#include <cpuinfo.h>
#include <cpufreq.h>

// Other libraries needed
#include <string>
#include <vector>

// Local libraries
#include "abscluster.hpp"
#include "abscore.hpp"
#include "abslogi.hpp"
//#include "syscore.hpp"

// Append AbsProc to SysCore namespace
namespace SysCore {
  /*
   * AbsProc is an abstract processor / CPU
   * class to handle accessing of utilization
   * and settings.
   * 
   * This class combines a wrapping of cpuinfo_package,
   * cpuinfo_core, cpuinfo_cluster, and cpuinfo_processor, and
   * it is instantiated from a cpuinfo_package.
   */
  class AbsProc {
  private:
    // List of packages
    static std::vector<AbsProc> packages;
    
    // Library
    static bool lib_init();
    static void lib_deinit();
    static void init_fatal();
    
    // Load components by package number
    bool load_clusters(uint32_t, std::vector<AbsCluster>*);
    bool load_cores(uint32_t, std::vector<AbsCore>*);
    bool load_processors(uint32_t, std::vector<AbsLogi>*);
    
    // Instance methods and variables
    std::string name;
    std::string vendor;
    // First logical processor, physical core, or cluster
    // on this package.
    uint logi_start, core_start, clust_start;
    // Count of all the local processors, cores, and
    // clusters on this package
    uint logi_cnt, core_cnt, clust_cnt;
    
    // Lists of logi processors, clusters, and core on this package
    std::vector<SysCore::AbsLogi> l_units;
    std::vector<SysCore::AbsCore> l_cores;
    std::vector<SysCore::AbsCluster> l_clus;
  protected:
    // Fill methods -- attach components to the package
    bool load();
  public:
    static AbsProc const get(uint); // Get a processor
    static uint load_units(); // Populate the units
    static uint count_units(); // Count the units loaded
    
    // Constructor will assemble a processor with a passed
    // cpuinfo_package object from the C side.
    AbsProc(const cpuinfo_package*);
    ~AbsProc(); // Destructor
    
    // Count the number of processors, clusters, or core
    uint count_procs(); // Logical processors (hardware threads)
    uint count_cores(); // Physical cores
    uint count_clusters(); // Logical processor groups
    
    // Name of the package
    std::string get_name();
  }; // End AbsProc
} // End namespace appendent
#endif