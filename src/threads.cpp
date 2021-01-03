#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <sys/types.h>
#include <unistd.h>

#include <atomic>
#include <type_traits>

#include "threads.hpp"

namespace tracey {

// Assert that the type for process_id set in the header matches that in
// <sys/types.h>. It is tested here, to avoid poluting the global namespace with
// the contents of <sys/types.h>
static_assert(std::is_same_v<process_id, pid_t>,
              "trace::process_id is not the same type as pid_t");

process_id local_thread_id() {
    //static std::atomic<thread_id> num_threads(0);
    //thread_local thread_id tid = num_threads++;
    thread_local process_id tid = gettid();
    return tid;
}

process_id local_process_id() {
    return getpid();
}

} // namespace tracey
