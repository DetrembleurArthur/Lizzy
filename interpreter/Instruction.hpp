#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include "Callable.hpp"
#include <vector>
#include "ActionBundle.hpp"

namespace lizzy
{
    class Instruction : public Callable
    {
    private:
        std::vector<Callable> arguments;
        ProtoMap& protoMap;
    public:
        Instruction(ProtoMap& runnable);
        Instruction& push(const Callable& arg);
        Instruction& push(Callable&& arg);
        LZDataType *getResult() const override;
    };
}


#endif
