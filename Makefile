# Makefile
BINDIR = bin/
TESTDIR = test/
BINNAME = syscore
TESTNAME = $(BINNAME)-test

T_CFLAGS = -std=c++17
R_CLFAGS = -std=c++17 -O2
LDFLAGS = -lprocps -lcpuinfo -lstdc++

INCLUDE = lib/*

SysCoreRelease: $(INCLUDE)
	g++ $(R_CFLAGS) -o $(BINDIR)$(BINNAME) $(INCLUDE) $(LDFLAGS)

SysCoreTest: $(INCLUDE)
	g++ $(T_CFLAGS) -o $(TESTDIR)$(TESTNAME) $(INCLUDE) $(LDFLAGS)
	
.PHONY: test clean

release: SysCoreRelease

test: SysCoreTest
	$(TESTDIR)$(TESTNAME)
	
clean:
	rm -f $(TESTDIR)$(TESTNAME)
	
purge: clean
	rm -f $(BINDIR)$(BINNAME)