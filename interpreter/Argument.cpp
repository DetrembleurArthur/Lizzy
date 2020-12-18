#include "Argument.hpp"

using namespace std;
using namespace lizzy;

Argument::Argument() : Argument(nullptr)
{

}

Argument::Argument(LZDataType* result) : result(result)
{
    
}

Argument::~Argument()
{
    if(this->result)
        delete this->result;
}

void Argument::setResult(LZDataType *result)
{
    this->result = result;
}

LZDataType *Argument::getResult() const
{
    return result;
}
