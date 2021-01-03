#include <iostream>
#include <omp.h>

#include <tracey/tracey.hpp>

int main() {
    tracey::context ctx;

    #pragma omp parallel
    {
        auto tid = omp_get_thread_num();
        auto id = ctx.id("io");
        #pragma omp critical
        {
            ctx.begin_event(id);
            ctx.end_event();
        }
    }

    return 0;
}
