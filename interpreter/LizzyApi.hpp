#ifndef LIZZY_API_HPP
#define LIZZY_API_HPP
#include "Package.hpp"


namespace lizzy
{
    namespace api
    {
        typedef void (*Api)(Package&);
        void connect_api(Package& apiPkg);
        LZDataType *print_1_str_cmd(Arguments args);
    }
}


#endif
