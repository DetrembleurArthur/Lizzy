#include "LZId.hpp"


using namespace std;
using namespace lizzy;


const std::string LZId::type = "LZId";



LZId::LZId() : LZId("")
{

}

LZId::LZId(const string& value) : LZPrimitive<string>()
{
    setValue(value);
}


LZId::~LZId()
{

}

std::string LZId::getId() const
{
    return LZId::type;
}

string LZId::toString()
{
    return getValue();
}

long LZId::toInt()
{
    throw LZException("LZId can not be cast as LZInteger");
}

double LZId::toFloat()
{
    throw LZException("LZId can not be cast as LZFloat");
}

bool LZId::toBool()
{
    throw LZException("LZId can not be cast as LZBool");
}

void LZId::setValue(std::string value)
{
    LZPrimitive<string>::setValue(value);
}

void LZId::setFromString(const std::string& value)
{
    setValue(value);
}
