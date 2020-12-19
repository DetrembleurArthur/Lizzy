#include "Executer.hpp"


using namespace std;
using namespace lizzy;


Executer::Executer()
{

}

Executer::~Executer()
{
    if(env)
        delete env;
    for(auto *result : lostResults)
    {
        delete result;
    }
}

void Executer::setEnv(ExecutionEnv *env)
{
    this->env = env;
}

void Executer::execute()
{
    Debug::loginfo("execution...");
    int& iptr = env->getIPtr();
    auto *instructions = env->getInstructions();
    for(iptr = 0; iptr < instructions->size(); iptr++)
    {
        (*instructions)[iptr]->setEnv(env);
        LZDataType *result = (*instructions)[iptr]->getResult();
        if(result)
            lostResults.push_back(result);
    }
}

std::vector<LZDataType *>& Executer::getLostResults()
{
    return lostResults;
}
