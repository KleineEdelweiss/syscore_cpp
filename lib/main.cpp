// lib/main.cpp

// Regular libraries
#include <cstdlib>
#include <iostream>

// SysCore
#include "syscore.hpp"

// Entry point
int main(int argc, char **args) {
  AbstractProcessor proc = AbstractProcessor();
  int ct = AbstractProcessor::count_pkgs();
  
  std::cout << "The total number of packages on the system is: "
    << ct << std::endl;
  std::cout << "Loading in processor..." << std::endl;
  proc.load_pkg(ct);
  std::cout << "This package has: " << proc.curr_count()
    << " logical processing units" << std::endl;
  std::cout << "Name of this package is: "
    << proc.curr_name() << std::endl;
  return 0;
} // End entry point