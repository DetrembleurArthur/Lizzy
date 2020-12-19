#ifndef EXECUTION_ENV_HPP
#define EXECUTION_ENV_HPP
#include <vector>
#include <string>
#include "DataStack.hpp"
#include "BranchController.hpp"


namespace lizzy
{
    class Executer;
    class Instruction;
    class ExecutionEnv
    {
    private:
        std::vector<Instruction *> *instructions = nullptr;
        BranchController *branchController = nullptr;
        DataStack *dataStack = nullptr;
        int iptr = -1;
    public:
        virtual ~ExecutionEnv();
        std::vector<Instruction *> *getInstructions();
        BranchController *getBranchController();
        DataStack *getDataStack();
        int& getIPtr();
        void setInstructions(std::vector<Instruction *> *instructions);
        void setBranchController(BranchController *branchController);
        void setDataStack(DataStack *dataStack);
        void setIPtr(int iptr);
        friend class Executer;
    };
}


#endif

