#include "LZInteger.hpp"


using namespace std;
using namespace lizzy;


const std::string LZInteger::type = typeid(LZInteger).name();


LZInteger::LZInteger() : LZInteger(0L)
{

}

LZInteger::LZInteger(long value) : LZPrimitive<long>(value)
{

}

LZInteger::LZInteger(const std::string& value)
{
    setFromString(value);
}

LZInteger::LZInteger(const LZInteger& value) : LZInteger(value.getValue())
{

}

LZInteger::~LZInteger()
{

}

string LZInteger::toString()
{
    return to_string(getValue());
}

long LZInteger::toInt()
{
    return getValue();
}

double LZInteger::toFloat()
{
    return (double)getValue();
}

bool LZInteger::toBool()
{
    return getValue() != 0;
}

void LZInteger::setFromString(const std::string& value)
{
    if(Parser::isInteger(value))
    {
        setValue(atoi(value.c_str()));
    }
    else
    {
        throw LZException("\"" + value + "\" is not a LZInteger");
    }
}
