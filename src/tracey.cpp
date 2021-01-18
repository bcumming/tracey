#include <iostream>
#include <atomic>
#include <string_view>
#include <vector>

#include <fmt/format.h>
#include <fmt/ostream.h>

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
    process_id pid_;

    context_impl(std::size_t capacity);

    void reset_clock();
    void begin_event(trace_id id);
    void begin_event(std::string_view name);
    void end_event();
    void to_json(std::ostream&);
    trace_id id(std::string_view name);
};

context_impl::context_impl(std::size_t capacity):
    events_(capacity), capacity_(capacity), pid_(local_process_id())
{
    std::cout << "TRACEY: init\n";
}

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

void context_impl::to_json(std::ostream& fid) {
    fid << "[";

    bool first = true;
    for (std::size_t i=0; i<event_count_; ++i) {
        const auto& e = events_[i];
        if (!first) {
            fmt::print(fid, ",\n ");
        }
        first = false;
        if (e.kind==event_kind::begin) {
            fmt::print(fid, "{{\"name\":\"{}\",\"ph\":\"B\",", ids_.name(e.id));
        }
        else {
            fmt::print(fid, "{{\"ph\":\"E\",");
        }
        fmt::print(fid, "\"pid\":{},\"tid\":{},\"ts\":{:.3f}}}", pid_, e.tid, (e.ts-t_start_)/1000.);
    }

    fmt::print(fid, "]\n");
}

context::context() {
    impl_ = new context_impl(1<<20);
    impl_->reset_clock();
}

context::~context() {
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

void context::to_json(std::ostream& fid) {
    return impl_->to_json(fid);
}

} // namespace tracey
