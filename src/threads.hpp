#pragma once

#include <cstdint>

namespace tracey {

/// Identifier assigned to each thread.
/// Threads are numbered contiguousely, starting at zero.
using thread_id = std::uint16_t;

thread_id local_thread_id();

} // namespace tracey
