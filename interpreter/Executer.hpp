#ifndef EXECUTER_HPP
#define EXECUTER_HPP
#include "Instruction.hpp"
#include "BranchController.hpp"
#include "DataStack.hpp"


namespace lizzy
{
    class Executer
    {
    private:
        std::vector<LZDataType *> lostResults;
        ExecutionEnv *env = nullptr;
    public:
        Executer();
        virtual ~Executer();
        void setEnv(ExecutionEnv *env);
        void execute();
        std::vector<LZDataType *>& getLostResults();
    };
}



#endif
