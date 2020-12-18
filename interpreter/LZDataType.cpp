#include "LZDataType.hpp"

using namespace std;
using namespace lizzy;


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
