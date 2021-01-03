set(tracey_sources
    event.cpp
    id.cpp
    tracey.cpp
    threads.cpp
    clock.cpp
)

# create the tracey library
add_library(tracey
    ${tracey_sources}
)

target_link_libraries(tracey PUBLIC tracey_headers)

