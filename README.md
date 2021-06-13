### OVERVIEW ###
C++ wrapping for some Linux system-monitoring C libraries that I intend to wrap further. Although these will be able to be used on their own, once finished, I intend to wrap them in Ruby. This kind of makes it "experimental". I am using this repo to store tests, because some of these tests have grown quite large unto themselves, and a few previous tests created very confusing local management.

### USAGE ###
-

### INSTALLATION ###
If you wish to test this on its own, feel free to clone the repo. It currently requires ``libprocps``, ``libcpuinfo``, and ``libcpufreq``.

[NOTE (AND RANT)]: This will likely have additions, and it will also possibly have deletions, as the libraries this project currently wraps are already not very efficient, so I will probably write my own custom implementation for at least some of it, as I still have not even seen a way to monitor usage on a per-core basis from it... at that point, it provides very little benefit not offered by writing it up from scratch -- the original reason to wrap was to _AVOID_ reading files in Ruby (due to high-frequency reads and high-overhead text-parsing), but if the C library is still doing that, I might as well just custom allocate the whole process in C++, so it jives with the rest of the wrapper (no reason to wrap C structs in C++ classes, etc.)...

### TODO ###
1) Get it to work
1) Update documentation
1) Wrap it in my other Ruby projects