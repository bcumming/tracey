#pragma once

#include <chrono>
#include <cstdint>
#include <ostream>

#include <tracey/tracey.hpp>

#include "clock.hpp"
#include "threads.hpp"

namespace tracey {

enum class event_kind: std::uint8_t {begin, end};

struct event {
    /// The time stamp of the event.
    timestamp_ns ts;
    /// The trace id which can be used to look up the name.
    trace_id id = nop_trace_id;
    /// The thread on which the event occurred
    thread_id tid;
    /// The type of event.
    event_kind kind;
};

std::ostream& operator<<(std::ostream&, const event&);

} // namespace tracey
