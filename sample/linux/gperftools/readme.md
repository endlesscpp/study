###1. tcmalloc
1. install
sudo apt-get install libgoogle-perftools-dev

1. usage:
link with the "-ltcmalloc" linker flag. or link libtcmalloc_minimal if does NOT need heap profiler.

or:
$ LD_PRELOAD="/usr/lib/libtcmalloc.so" 

###2. heap checker
1. link with tcmalloc, and create a build: testgperf
c++ -std=c++11 main.cpp -g -O0 -ltcmalloc -o testgperf

2. export PPROF_PATH=/usr/bin/google-pprof
3. HEAPCHECK=normal .testgperf

###3. heap profiler


###4. cpu profiler
1. -lprofiler
or % env LD_PRELOAD="/usr/lib/libprofiler.so" <binary>
2. % env CPUPROFILE=my.prof a.out
3. convert profile.log to callgrind compatible format
$ pprof --callgrind ./cpuload profile.log > profile.callgrind

open profile.callgrind with kcachegrind
$ kcachegrind profile.callgrind


maybe need to manually insert:
```c
#include <gperftools/profiler.h>
int main()
{
    ProfilerStart("my.prof");
    ...
    ProfilerStop();
}
```

###4.2 or using valgrind
```bash
# build the program (no special flags are needed)
$ g++ -std=c++11 cpuload.cpp -o cpuload

# run the program with callgrind; generates a file callgrind.out.12345 that can be viewed with kcachegrind
$ valgrind --tool=callgrind ./cpuload

# open profile.callgrind with kcachegrind
$ kcachegrind profile.callgrind
```

###refs: 
https://gperftools.github.io/gperftools/
https://github.com/gperftools/gperftools
https://github.com/google/pprof
https://gernotklingler.com/blog/gprof-valgrind-gperftools-evaluation-tools-application-level-cpu-profiling-linux/
