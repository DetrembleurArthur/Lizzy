#include "Argument.hpp"

using namespace std;
using namespace lizzy;

Argument::Argument() : Argument(nullptr)
{

}

Argument::Argument(LZDataType* result) : result(result)
{
    
}


void Argument::setResult(LZDataType *result)
{
    this->result = result;
}

LZDataType *Argument::getResult() const
{
    return result;
}
