#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include <vector>
#include "ActionBundle.hpp"
#include "Command.hpp"
#include "Argument.hpp"

namespace lizzy
{
    class Instruction : public Callable
    {
    private:
        std::vector<Callable *> arguments;
        ProtoMap& protoMap;
        Command& command;
        Instruction *super;
    public:
        Instruction(Command& command, ProtoMap& runnable, Instruction *super=nullptr);
        Instruction& push(Callable* arg);
        LZDataType *getResult() const override;
        std::string getStackTrace(std::string message="") const;
        void throwEx(std::string message) const noexcept(false);
    };
}


#endif
