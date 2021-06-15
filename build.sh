#! /bin/bash
# build.sh

# Get the compilation type argument
if [[ $1 = "test" ]]; then
  comp=$1 # Test compile
else
  comp="release" # Anything else is release
fi

# Make the program
make -j`nproc` $comp