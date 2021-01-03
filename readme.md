# Tracey

A C++ library for instrumenting multithreaded applications to produce trace profiles in the Chrome "Trace Event Format".

## Design goals

Tracey is designed to be low overhead for HPC applications

* Support for duration events: regions of time on a single thread marked with a begin and end
    * record time taken
    * optionally report performance counters.
* Support for automatic registration of CUDA kernels
