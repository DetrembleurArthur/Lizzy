#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP
#include "Callable.hpp"
#include <vector>

namespace lizzy
{
    typedef std::string (*Runnable)(const std::vector<Callable>&);
    class Instruction : public Callable
    {
    private:
        std::vector<Callable> arguments;
        Runnable runnable;
    public:
        Instruction();
        Instruction(Runnable runnable);
        Instruction(const Instruction& other);
        Instruction(Instruction&& other);
        void setRunnable(Runnable runnable);
        Runnable getRunnable() const;
        Instruction& push(const Callable& arg);
        Instruction& push(Callable&& arg);
        std::string getResult() const override;
    };
}


#endif
