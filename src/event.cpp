#include <chrono>
#include <cstdint>
#include <ostream>

#include <tracey/tracey.hpp>

#include "event.hpp"

namespace tracey {

std::ostream& operator<<(std::ostream& o, const event& e) {
    return
      o << "(event "
        <<  e.ts << " "
        <<  e.id << " "
        <<  e.tid << " "
        <<  (e.kind==event_kind::begin? "begin": "end")
        << ")";
}

} // namespace tracey
