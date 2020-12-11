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
    stack.push_back(var);
    return stack.size() - 1;
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

