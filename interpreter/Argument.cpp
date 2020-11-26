#include "Argument.hpp"

using namespace std;
using namespace lizzy;

Argument::Argument() : Argument("/")
{

}

Argument::Argument(const string& result) : result(result)
{
    
}

Argument::Argument(const Argument& other) : Argument(other.getResult())
{

}

Argument::Argument(Argument&& other) : Argument(other.getResult())
{

}

void Argument::setResult(const string& result)
{
    this->result = result;
}

string Argument::getResult() const
{
    return result;
}
