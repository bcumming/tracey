#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include <omp.h>

#include <tracey/tracey.hpp>

int main() {
    using namespace std::chrono_literals;
    tracey::context ctx;

    #pragma omp parallel
    {
        std::cout << "thread " << omp_get_thread_num() << "\n";
    }

    auto id_io = ctx.id("io");
    auto id_run = ctx.id("run");
    #pragma omp parallel
    {
        auto tid = omp_get_thread_num();
        #pragma omp critical
        {
            ctx.begin_event(id_io);
            std::this_thread::sleep_for((tid+1)*10ms);
            ctx.end_event();
        }
    }

    #pragma omp parallel
    {
        auto tid = omp_get_thread_num();
        #pragma omp critical
        {
            ctx.begin_event(id_run);
            std::this_thread::sleep_for((tid+1)*1ms);
            ctx.end_event();
        }
    }

    auto fid = std::ofstream("omp-prof.json");
    ctx.to_json(fid);
    fid.close();

    return 0;
}
