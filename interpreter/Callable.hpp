#ifndef CALLABLE_HPP
#define CALLABLE_HPP
#include <string>
#include "LZDataType.hpp"

namespace lizzy
{
    class Callable
    {
    public:
        virtual ~Callable();
        virtual LZDataType *getResult() const = 0;
    };
}


#endif
