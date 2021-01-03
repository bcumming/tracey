#include <atomic>

#include "threads.hpp"

namespace tracey {

thread_id local_thread_id() {
    static std::atomic<thread_id> num_threads(0);
    thread_local thread_id tid = num_threads++;
    return tid;
}

} // namespace tracey
