#include "LZVariable.hpp"

using namespace std;
using namespace lizzy;


LZVariable::LZVariable(const std::string& name) : LZVariable(name, nullptr)
{

}

LZVariable::LZVariable(const std::string& name, LZDataType *other) : reference(other)
{
    if(name.size() > 1)
    {
        Debug::loginfo("create var " + name);
        this->name = name.substr(1);
    }
    else
        throw LZException("variable name is empty");
}

LZVariable::~LZVariable()
{

}

std::string LZVariable::getId() const
{
    return reference ? reference->getId() : "LZVariable";
}

std::string LZVariable::toString()
{
    if(reference)
        return reference->toString();
    return "(null)";
}

long LZVariable::toInt()
{
    if(reference)
        return reference->toInt();
    throw LZException("reference to 'null'");
}

double LZVariable::toFloat()
{
    if(reference)
        return reference->toFloat();
    throw LZException("reference to 'null'");
}

bool LZVariable::toBool()
{
    if(reference)
        return reference->toBool();
    throw LZException("reference to 'null'");
}

LZDataType *LZVariable::getValue()
{
    return reference;
}

void LZVariable::setValue(LZDataType *reference)
{
    this->reference = reference;
}

bool LZVariable::isNull() const
{
    return not reference;
}

std::string LZVariable::getName() const
{
    return name;
}
