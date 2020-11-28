#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP
#include "Callable.hpp"

namespace lizzy
{
    class Argument : public Callable
    {
    private:
        LZDataType *result;
    public:
        Argument();
        Argument(LZDataType* result);
        void setResult(LZDataType* result);
        LZDataType *getResult() const override;
    };
}


#endif
