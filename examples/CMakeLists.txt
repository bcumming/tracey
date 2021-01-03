add_custom_target(examples DEPENDS)

FIND_PACKAGE(OpenMP)
if(OPENMP_FOUND)
    add_executable(omp EXCLUDE_FROM_ALL omp.cpp)
    target_link_libraries(omp PRIVATE tracey OpenMP::OpenMP_CXX)
    add_dependencies(examples omp)
endif()

