#pragma once

#include <atomic>
#include <mutex>
#include <string_view>
#include <unordered_map>
#include <vector>

#include <tracey/tracey.hpp>

namespace tracey {

class id_dictionary {
public:
    trace_id lookup(std::string_view name);
    std::string name(trace_id id) const;
    std::size_t size() const;
    std::vector<std::string> names() const;

private:
    std::atomic<trace_id> count_ = 0;
    mutable std::mutex mutex_;
    std::vector<std::string> names_;
    std::unordered_map<std::string_view, trace_id> map_;
};

trace_id unique_trace_id(std::string_view);

} // namespace tracey
