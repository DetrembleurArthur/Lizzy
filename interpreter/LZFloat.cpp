#include "LZFloat.hpp"


using namespace std;
using namespace lizzy;


const std::string LZFloat::type = typeid(LZFloat).name();


LZFloat::LZFloat() : LZFloat(0.0)
{

}

LZFloat::LZFloat(double value) : LZPrimitive<double>(value)
{

}

LZFloat::LZFloat(const std::string& value)
{
    setFromString(value);
}

LZFloat::LZFloat(const LZFloat& value) : LZFloat(value.getValue())
{

}

LZFloat::~LZFloat()
{

}

string LZFloat::toString()
{
    return to_string(getValue());
}

long LZFloat::toInt()
{
    return (long)getValue();
}

double LZFloat::toFloat()
{
    return getValue();
}

bool LZFloat::toBool()
{
    return getValue() != 0.0;
}

void LZFloat::setFromString(const std::string& value)
{
    if(Parser::isFloat(value))
    {
        setValue(atof(value.c_str()));
    }
    else
    {
        throw LZException("\"" + value + "\" is not a LZFloat");
    }
}

