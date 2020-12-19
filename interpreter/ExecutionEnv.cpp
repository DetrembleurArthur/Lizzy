#include "ExecutionEnv.hpp"

using namespace lizzy;
using namespace std;

ExecutionEnv::~ExecutionEnv()
{
    if(instructions)
    {
        for(auto *instr : *instructions)
        {
            delete instr;
        }
        delete instructions;
    }
    if(dataStack)
        delete dataStack;
    if(branchController)
        delete branchController;
}

std::vector<Instruction *> *ExecutionEnv::getInstructions()
{
    return instructions;
}

BranchController *ExecutionEnv::getBranchController()
{
    return branchController;
}

DataStack *ExecutionEnv::getDataStack()
{
    return dataStack;
}

int& ExecutionEnv::getIPtr()
{
    return iptr;
}

void ExecutionEnv::setInstructions(std::vector<Instruction *> *instructions)
{
    this->instructions = instructions;
}

void ExecutionEnv::setBranchController(BranchController *branchController)
{
    this->branchController = branchController;
}

void ExecutionEnv::setDataStack(DataStack *dataStack)
{
    this->dataStack = dataStack;
}

void ExecutionEnv::setIPtr(int iptr)
{
    this->iptr = iptr;
}
