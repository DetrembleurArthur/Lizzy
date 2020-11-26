#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP
#include "Callable.hpp"

namespace lizzy
{
    class Argument : public Callable
    {
    private:
        std::string result;
    public:
        Argument();
        Argument(const std::string& result);
        Argument(const Argument& other);
        Argument(Argument&& other);
        void setResult(const std::string& result);
        std::string getResult() const override;
    };
}


#endif
