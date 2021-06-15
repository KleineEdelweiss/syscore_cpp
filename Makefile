# Makefile
# Project variables
BINDIR = bin/
TESTDIR = test/
BINNAME = syscore
TESTNAME = $(BINNAME)-test

# Compilation and environment variables
CPP_VER = -std=c++17
GEN_OPT = -pipe
R_OPT_LVL = -O2

# Flag interpolation by Compilation type
T_CFLAGS = $(CPP_VER) $(GEN_OPT)
R_CLFAGS = $(T_CFLAGS) $(R_OPT_LVL)

# Loader flags
LDFLAGS = -lprocps -lcpuinfo -lstdc++ -lcpufreq

# Library directory
LIB = lib/*
#SYSCORE_BASE = lib/syscore/*
#PROC = lib/syscore/absproc/*
#LOGI = lib/syscore/abslogi/*
#CORE = lib/syscore/abscore/*
#CLUS = lib/syscore/absclus/*
#INIT = lib/syscore_init.hpp
#MAIN = lib/main.cpp
#INCLUDE = $(LIB) $(SYSCORE_BASE) $(PROC) $(LOGI) $(CORE) $(CLUS)
#INCLUDE = \
#	$(wildcard lib/*.hpp) \
#	$(wildcard lib/*.cpp) \
#	$(wildcard lib/syscore/*.hpp) \
#	$(wildcard lib/syscore/*.cpp) 
#	$(wildcard lib/syscore/*/*.hpp) \
#	$(wildcard lib/syscore/*/*.cpp)
#	$(wildcard lib/syscore/abslogi/*.hpp) \
#	$(wildcard lib/syscore/abslogi/*.cpp) \
#	$(wildcard lib/*.hpp) \
#	$(wildcard lib/*.hpp) \
#	$(wildcard lib/*.hpp) \
#	$(wildcard lib/*.hpp) \
#	$(wildcard lib/*.hpp) \
#	$(wildcard lib/*.hpp) \
#	$(wildcard lib/*.hpp)
#INCLUDE_FIX=$(foreach d, $(INCLUDE), -I$d)
INCLUDE = $(LIB)

# Print the include paths
dirs:
	echo $(INCLUDE)

# Release job
SysCoreRelease: $(INCLUDE)
	g++ $(R_CFLAGS) -o $(BINDIR)$(BINNAME) $(INCLUDE) $(LDFLAGS)
#	for dir in $(INCLUDE); do \
#		g++ $(R_CFLAGS) -o $(BINDIR)$(BINNAME) $$dir $(LDFLAGS); \
#	done

# Test job
SysCoreTest: $(INCLUDE)
	g++ $(T_CFLAGS) -o $(TESTDIR)$(TESTNAME) $(INCLUDE) $(LDFLAGS)
#	for dir in $(INCLUDE); do \
#		g++ $(T_CFLAGS) -o $(TESTDIR)$(TESTNAME) $$dir $(LDFLAGS); \
#	done
	
.PHONY: test clean

# Attach the job labels and extra commands
release: SysCoreRelease

test: SysCoreTest
	$(TESTDIR)$(TESTNAME)

# Cleanup test directory
clean:
	rm -f $(TESTDIR)$(TESTNAME)

# AND release directory
purge: clean
	rm -f $(BINDIR)$(BINNAME)