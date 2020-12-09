#ifndef LIZZY_API_HPP
#define LIZZY_API_HPP
#include "Package.hpp"
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <Windows.h>
#define sleep(ms) Sleep(ms)
#elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(unix__) || defined(unix) || defined(__linux__)
#include <unistd.h>
#define sleep(ms) usleep(ms * 1000);
#endif

namespace lizzy
{
    namespace api
    {
        typedef void (*Api)(Package&);
        void connect_api(Package& apiPkg);
        LZDataType *print_1_str_cmd(Arguments args);
        LZDataType *delay_1_flt_cmd(Arguments args);
        LZDataType *delay_0_flt_cmd(Arguments args);
        LZDataType *delay_ns_1_flt_cmd(Arguments args);
    }
}


#endif
