#include <iostream>
#include <atomic>
#include <string_view>
#include <vector>

#include <tracey/tracey.hpp>

#include "event.hpp"
#include "id.hpp"
#include "clock.hpp"
#include "threads.hpp"

namespace tracey {

struct context_impl {
    id_dictionary ids_;
    std::vector<event> events_;
    std::atomic<std::size_t> event_count_ = 0;
    std::size_t capacity_;
    timestamp_ns t_start_;

    context_impl(std::size_t capacity);

    void reset_clock();
    void begin_event(trace_id id);
    void begin_event(std::string_view name);
    void end_event();
    trace_id id(std::string_view name);
};

context_impl::context_impl(std::size_t capacity):
    events_(capacity), capacity_(capacity)
{}

void context_impl::begin_event(trace_id id) {
    if (auto i=event_count_++; i<capacity_) {
        const auto tid = local_thread_id();
        const auto ts  = clock_ns();
        events_[i] = {ts, id, tid, event_kind::begin};
    }
}

void context_impl::begin_event(std::string_view name) {
    if (auto i=event_count_++; i<capacity_) {
        const auto tid = local_thread_id();
        const auto ts  = clock_ns();
        const trace_id id = ids_.lookup(name);
        events_[i] = {ts, id, tid, event_kind::begin};
    }
}

void context_impl::end_event() {
    if (auto i=event_count_++; i<capacity_) {
        const auto tid = local_thread_id();
        const auto ts  = clock_ns();
        events_[i] = {ts, nop_trace_id, tid, event_kind::end};
    }
}

trace_id context_impl::id(std::string_view name) {
    return ids_.lookup(name);
}

void context_impl::reset_clock() {
    t_start_ = clock_ns();
}

context::context() {
    impl_ = new context_impl(1<<20);
    impl_->reset_clock();
}

context::~context() {
    std::cout << ":: events " << impl_->event_count_ << "\n";
    for (auto i=0; i<impl_->event_count_; ++i) {
        std::cout << "  " << impl_->events_[i] << "\n";
    }
    delete impl_;
}

void context::begin_event(trace_id id) {
    impl_->begin_event(id);
}
void context::begin_event(std::string_view name) {
    impl_->begin_event(name);
}

void context::end_event() {
    impl_->end_event();
}

void context::reset_clock() {
    impl_->reset_clock();
}

trace_id context::id(std::string_view name) {
    return impl_->id(name);
}

} // namespace tracey
