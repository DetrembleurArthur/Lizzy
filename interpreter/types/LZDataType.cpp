#include "LZDataType.hpp"

using namespace std;
using namespace lizzy;


LZDataType::LZDataType() : LZDataType(nullptr)
{

}

LZDataType::LZDataType(void *ptr) : value(ptr)
{

}


LZDataType::~LZDataType()
{
    if(value != nullptr)
        free(value);
}

string LZDataType::getId() const
{
    return typeid(*this).name();
}

void *LZDataType::getValue() const
{
    return value;
}


void LZDataType::setValue(void *value)
{
    if(this->value != nullptr)
        free(this->value);
    this->value = value;
}

std::string LZDataType::toString()
{
    return "[LZDataType]@" + getId();
}
