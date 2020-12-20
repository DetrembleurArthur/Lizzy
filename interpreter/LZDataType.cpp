#include "LZDataType.hpp"

using namespace std;
using namespace lizzy;

const std::string LZDataType::type = "LZDataType";

LZDataType::LZDataType()
{
    Debug::logfatal("CREATE DATA");
}



LZDataType::~LZDataType()
{
    Debug::logfatal("REMOVE DATA");
}

string LZDataType::getId() const
{
    return "LZDataType";
}

size_t LZDataType::getHashCode() const
{
    hash<string> hashGen;
    return hashGen(getId());
}


std::string LZDataType::toString()
{
    return "";
}

long LZDataType::toInt()
{
    return 0;
}

double LZDataType::toFloat()
{
    return 0.0;
}

bool LZDataType::toBool()
{
    return false;
}

int LZDataType::isDataType(LZDataType *other)
{
    return -1;
}

int LZDataType::isInteger(LZDataType *data)
{
    try
    {
        if(data->getId() != "LZInteger")
        {
            data->toInt();
            return -1;
        }
    }
    catch(const LZException& e)
    {
        return 0;
    }
    return 1;
}

int LZDataType::isFloat(LZDataType *data)
{
    try
    {
        if(data->getId() != "LZFloat")
        {
            data->toFloat();
            return -1;
        }
    }
    catch(const LZException& e)
    {
        return 0;
    }
    return 1;
}

int LZDataType::isBool(LZDataType *data)
{
    try
    {
        if(data->getId() != "LZBool")
        {
            data->toBool();
            return -1;
        }
    }
    catch(const LZException& e)
    {
        return 0;
    }
    return 1;
}

int LZDataType::isString(LZDataType *data)
{
    try
    {
        if(data->getId() != "LZString")
        {
            data->toString();
            return -1;
        }
    }
    catch(const LZException& e)
    {
        return 0;
    }
    return 1;
}

int LZDataType::isId(LZDataType *data)
{
    return data->getId() == "LZId";
}
