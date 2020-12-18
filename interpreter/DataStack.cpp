#include "DataStack.hpp"

using namespace std;
using namespace lizzy;


DataStack::DataStack()
{

}

DataStack::~DataStack()
{
    for(LZVariable *var : stack)
    {
        if(var)
            delete var;
    }
}

DataStack *DataStack::create()
{
    return new DataStack();
}

int DataStack::push(LZVariable *var)
{
    for(int i = contextPointers.top(); i < stack.size(); i++)
    {
        if(var->getName() == stack[i]->getName())
        {
            throw new LZException("'" + var->getName() + "' is duplicated");
        }
    }
    stack.push_back(var);
    return stack.size() - 1;
}

void DataStack::push()
{
    contextPointers.push(stack.size());
}

void DataStack::pop()
{
    if(not contextPointers.empty())
    {
        stack.erase(stack.begin() + contextPointers.top(), stack.end());
        contextPointers.pop();
    }
    else
    {
        throw LZException("no context to pop");
    }
}

size_t DataStack::variables() const
{
    return stack.size();
}

size_t DataStack::contexts() const
{
    return contextPointers.size() + 1;
}

LZVariable *DataStack::getVariable(const std::string& id)
{
    if(stack.size())
    {
        for(int i = stack.size() - 1; i >= 0; i++)
        {
            if(stack[i]->getName() == id)
                return stack[i];
        }
    }
    return nullptr;
}
