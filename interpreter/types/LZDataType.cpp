#include "LZDataType.hpp"

using namespace std;
using namespace lizzy;


LZDataType::LZDataType()
{

}



LZDataType::~LZDataType()
{
    
}

string LZDataType::getId() const
{
    return typeid(*this).name();
}


std::string LZDataType::toString()
{
    return "";
}

int LZDataType::toInt()
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
