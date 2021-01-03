#include <atomic>
#include <mutex>
#include <string_view>

#include "id.hpp"

namespace tracey {

std::size_t id_dictionary::size() const {
    return names_.size();
};

std::vector<std::string> id_dictionary::names() const {
    return names_;
}

trace_id id_dictionary::lookup(std::string_view name) {
    std::lock_guard<std::mutex> guard(mutex_);

    // If name already has an id associated with it, return the id.
    if (auto it = map_.find(name); it!=map_.end()) {
        return it->second;
    }

    // First add name to the list of names.
    names_.push_back(std::string{name});

    // Determine new id and assign to lookup table.
    auto id = count_++;
    map_[names_.back()] = id; // map_ holds a string_view of names_.back()
    return id;
}

std::string id_dictionary::name(trace_id id) const {
    std::lock_guard guard(mutex_);

    if (id<count_) {
        return names_[id];
    }

    throw std::runtime_error("tracey: trace id out of bounds.");
}

} // namespace tracey

