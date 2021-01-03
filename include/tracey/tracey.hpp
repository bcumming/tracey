#pragma once

#include <chrono>
#include <cstdint>
#include <string_view>

namespace tracey {


/// Id used for region identifiers.
using trace_id = std::uint32_t;
constexpr trace_id nop_trace_id = -1;

struct context_impl;

struct context {
    context_impl* impl_;

    context();
    ~context();

    void begin_event(trace_id);
    void begin_event(std::string_view);
    void end_event();
    void reset_clock();
    trace_id id(std::string_view);
};

#ifdef WITH_TRACEY

    // Start a trace
    #define TRACEY_START(name) \
        { \
            static trace_id tracey_id__ = tracey::unique_trace_id(#name); \
            tracey::start_trace(region_id__); \
        }

    // Stop a trace
    #define TRACEY_STOP tracey::stop_trace

#else

    #define TRACEY_START(name)
    #define TRACEY_STOP()

#endif

} // namespace tracey
