#ifndef CALLABLE_HPP
#define CALLABLE_HPP
#include <string>

namespace lizzy
{
    class Callable
    {
    public:
        virtual std::string getResult() const = 0;
    };
}


#endif
