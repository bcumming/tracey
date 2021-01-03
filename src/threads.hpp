#pragma once

#include <cstdint>

namespace tracey {

/// Corresponds to pid_t, defined in sys/types.h
/// These are defined separately to avoid polluting the global namespace with
/// the contents of sys/types.h. Checks are performed in threads.cpp to ensure
/// that process_id and pid_t are the same type.
using process_id = int;

process_id local_thread_id();
process_id local_process_id();

} // namespace tracey
