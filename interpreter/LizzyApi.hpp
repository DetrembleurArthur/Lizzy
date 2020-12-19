#ifndef LIZZY_API_HPP
#define LIZZY_API_HPP
#include "LizzyLangApi.hpp"

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
        void connect_api(Package& apiPkg);
        LZDataType *nop(Arguments args, ExecutionEnv *env);
    }
}


#endif
