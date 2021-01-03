#pragma once

#include <cstdint>

/// Time measured in miliseconds
using timestamp_ns = std::uint64_t;

namespace tracey {

timestamp_ns clock_ns();

} // namespace tracey

