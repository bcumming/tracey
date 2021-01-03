# set path for headers
add_library(tracey_headers INTERFACE)

target_include_directories(tracey_headers INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

