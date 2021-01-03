#define _POSIX_C_SOURCE 200809L
#include <time.h>

#include <cstdint>

#include "clock.hpp"

namespace tracey {

inline timestamp_ns posix_clock_gettime_ns(clockid_t clock) {
    timespec ts;
    if (clock_gettime(clock, &ts)) {
        return (unsigned long long)-1;
    }

    // According to SUS, we can assume tv_nsec is in [0, 1e9).

    timestamp_ns seconds = ts.tv_sec;
    timestamp_ns nanoseconds = 1000000000UL*seconds+(timestamp_ns)ts.tv_nsec;

    return nanoseconds;
};

timestamp_ns clock_ns() {
    return posix_clock_gettime_ns(CLOCK_MONOTONIC);
}

} // namespace tracey

