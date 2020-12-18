#include "Executer.hpp"


using namespace std;
using namespace lizzy;


Executer::Executer() : instructions(nullptr), dataStack(DataStack::create()), iptr(-1)
{

}

Executer::~Executer()
{
    if(instructions)
    {
        for(auto *instr : *instructions)
        {
            delete instr;
        }
        delete instructions;
    }
    for(auto *result : lostResults)
    {
        delete result;
    }
    delete dataStack;
}

void Executer::setInstructions(std::vector<Instruction *> *instructions)
{
    this->instructions = instructions;
}

void Executer::execute()
{
    Debug::loginfo("execution...");
    for(iptr = 0; iptr < instructions->size(); iptr++)
    {
        (*instructions)[iptr]->setDataStack(dataStack);
        LZDataType *result = (*instructions)[iptr]->getResult();
        if(result)
            lostResults.push_back(result);
    }
}

std::vector<LZDataType *>& Executer::getLostResults()
{
    return lostResults;
}
