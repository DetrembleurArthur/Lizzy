#include "Executer.hpp"


using namespace std;
using namespace lizzy;


Executer::Executer() : instructions(nullptr), iptr(-1)
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
        LZDataType *result = (*instructions)[iptr]->getResult();
        if(result)
            lostResults.push_back(result);
    }
}

std::vector<LZDataType *>& Executer::getLostResults()
{
    return lostResults;
}
