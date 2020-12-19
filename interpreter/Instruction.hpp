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
        ProtoMap *protoMap;
        bool undefined;
        Command *command;
        Instruction *super;
        ExecutionEnv **env;
        void setPEnv(ExecutionEnv **env);
    public:
        Instruction(Command *command);
        virtual ~Instruction();
        Instruction& push(Callable* arg);
        LZDataType *getResult() const override;
        std::string getStackTrace(std::string message="") const;
        Command *getCommand();
        void throwEx(std::string message) const noexcept(false);
        void setSuper(Instruction *super);
        void setProtoMap(ProtoMap *protoMap, bool undefined=false);
        void setEnv(ExecutionEnv *env);
    };
}


#endif
