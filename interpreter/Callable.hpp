#ifndef CALLABLE_HPP
#define CALLABLE_HPP
#include <string>
#include "types/LZDataType.hpp"

namespace lizzy
{
    class Callable
    {
    public:
        virtual LZDataType *getResult() const = 0;
    };
}


#endif
