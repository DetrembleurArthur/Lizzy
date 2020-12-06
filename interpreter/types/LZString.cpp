#include "LZString.hpp"


using namespace std;
using namespace lizzy;



LZString::LZString() : LZString("")
{

}

LZString::LZString(const string& value) : LZPrimitive<string>()
{
    setValue(value);
}

LZString::LZString(const LZString& value) : LZString(value.getValue())
{

}

LZString::~LZString()
{

}

string LZString::toString()
{
    return getValue();
}

long LZString::toInt()
{
    if(Parser::isInteger(getValue()) or Parser::isFloat(getValue()))
    {
        return atoi(getValue().c_str());
    }
    else if(Parser::isBool(getValue()))
    {
        return getValue() == "true";
    }
    throw LZException("\"" + getValue() + "\" can not be cast as LZInteger");
}

double LZString::toFloat()
{
    if(Parser::isInteger(getValue()) or Parser::isFloat(getValue()))
    {
        return atof(getValue().c_str());
    }
    else if(Parser::isBool(getValue()))
    {
        return getValue() == "true";
    }
    throw LZException("\"" + getValue() + "\" can not be cast as LZFloat");
}

bool LZString::toBool()
{
    if(Parser::isBool(getValue()))
    {
        return getValue() == "true";
    }
    throw LZException("\"" + getValue() + "\" can not be cast as LZBool");
}

void LZString::setValue(std::string value)
{
    if(Parser::isString(value))
    {
        LZPrimitive<string>::setValue(value.substr(1, value.size() - 2));
    }
    else
    {
        throw LZException("\"" + value + "\" is not a LZString");
    }
}

void LZString::setFromString(const std::string& value)
{
    setValue("\"" + value + "\"");
}
