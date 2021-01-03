#pragma once

#include <chrono>
#include <cstdint>
#include <ostream>
#include <string_view>

namespace tracey {


/// Id used for region identifiers.
using trace_id = std::uint32_t;
constexpr trace_id nop_trace_id = -1;

struct context_impl;

class context {
    /// PIMPLed implementation.
    context_impl* impl_;

public:
    context();
    ~context();

    /// Register the start of a trace, automatically recording the the
    /// thread id and start time.
    /// The trace_id must correspond to a trace_id registered beforehand
    /// via context::id(std::string_view).
    /// Thread safe.
    void begin_event(trace_id);

    /// Register the start of a trace, automatically recording the the
    /// thread id and start time.
    /// Thread safe.
    void begin_event(std::string_view);

    /// Register the start of a trace. This will automatically record the
    /// the thread id and start time.
    /// Thread safe.
    void end_event();

    /// Set the start time for the time stamps to the current time.
    /// By defalt this is zero, so all measurements will be relative to
    /// the start of the time epoch used by the system.
    /// Not thread safe.
    void reset_clock();

    /// Return the unique integral identifier associated with a
    /// trace region name.
    /// Thread safe.
    trace_id id(std::string_view);

    void to_json(std::ostream&);
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
