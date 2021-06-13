// include/syscore.cpp

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
#include <string>
#include <vector>

// This header
#include "syscore.hpp"

// Define the static class variables
int  AbstractProcessor :: count;
bool  AbstractProcessor :: lib_state;
std::vector<const cpuinfo_package *> AbstractProcessor :: packages;

// Fatal error message for if the library could not be initialized.
// Aborts program execution.
void AbstractProcessor :: init_fatal() {
  std::cerr << "::FATAL ERROR (AbstractProcessor):: Could not initialize 'cpuinfo'"
    << std::endl << "Aborting" << std::endl;
  abort();
} // End fatal error message and abort

/*
  * Initialize the library -- this should be
  * checked for all instances on creation.
  *
  * If the library is initialized, just return true.
  */
bool AbstractProcessor :: lib_initialize() {
  // Only init, if not already done
  if (!lib_state) {
    lib_state = cpuinfo_initialize();
    // Get a package count
    int pkg_cnt = cpuinfo_get_packages_count();
    for (int i = 0; i < pkg_cnt; i++) {
      const struct cpuinfo_package *item = cpuinfo_get_package(i);
      packages.push_back(item);
    }
  }
  return lib_state; // Return if the library was initialized
} // End library initialization

/* 
  * De-initialize the library and clear all the
  * existing static structs stored in the vectors.
  */
void AbstractProcessor :: lib_deinitialize() {
  if (lib_state && count < 1) {
    for (std::vector<const cpuinfo_package *>::iterator itr = packages.begin();
      itr != packages.end(); ++itr) {
      // Free the item
      delete *itr;
    }
    // Clean up the resources
    packages.clear();
    cpuinfo_deinitialize();
  }
} // End library de-initialization

// Count the packages
size_t AbstractProcessor :: count_pkgs() { return packages.size(); }

// Constructor
AbstractProcessor :: AbstractProcessor() {
  if (lib_initialize()) {
    this->pkg = NULL;
    count++;
  } else { init_fatal(); }
} // End constructor

// Destructor
AbstractProcessor :: ~AbstractProcessor() {
  delete this->pkg;
  this->pkg = NULL;
  lib_deinitialize();
} // End destructor

// Load in the current package's processors
int AbstractProcessor :: load_pkg(int index) {
  if (lib_initialize()) {
    int cnt = count_pkgs();
    if ((index <= cnt) && (index > 0)) {
      this->pkg = packages.at(index - 1);
      return 0;
    } else {
      std::cerr << "::WARNING (AbstractProcessor):: Index passed "
        << index << " exceeds package count of the system." << std::endl
        << "  Please change to value not exceeding: " << cnt
        << std::endl << "  No update was made to instance!!" << std::endl;
      return -1;
    }
  } else { init_fatal(); }
  return 0;
} // End current processor package loader

// Count the current package's logical processors
int AbstractProcessor :: curr_count() {
  if (lib_initialize()) {
    return this->pkg->processor_count;
  } else { init_fatal(); }
  return 0;
} // End current processor package's logical core count

// Load in the current package's processors
std::string AbstractProcessor :: curr_name() {
  std::string name = "";
  if (lib_initialize()) {
     name = std::string(this->pkg->name);
  } else { init_fatal(); }
  return name;
} // End current processor package name