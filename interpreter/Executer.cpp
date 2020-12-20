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
    }
}
