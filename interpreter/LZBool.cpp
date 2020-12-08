#include "LZBool.hpp"


using namespace std;
using namespace lizzy;



const std::string LZBool::type = typeid(LZBool).name();



LZBool::LZBool() : LZBool(false)
{

}

LZBool::LZBool(bool value) : LZPrimitive<bool>(value)
{

}

LZBool::LZBool(const LZBool& value) : LZBool(value.getValue())
{

}

LZBool::LZBool(const string& value)
{
    setFromString(value);
}

LZBool::~LZBool()
{

}

string LZBool::toString()
{
    return getValue() ? "true" : "false";
}

long LZBool::toInt()
{
    return (long)getValue();
}

double LZBool::toFloat()
{
    return (double)getValue();
}

bool LZBool::toBool()
{
    return getValue();
}

void LZBool::setFromString(const std::string& value)
{
    if(Parser::isBool(value))
    {
        setValue(value == "true");
    }
    else
    {
        throw LZException("\"" + value + "\" is not a LZBool");
    }
}
