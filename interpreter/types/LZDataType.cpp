#include "LZDataType.hpp"

using namespace std;
using namespace lizzy;


LZDataType::LZDataType() : value(nullptr)
{

}

string LZDataType::getId() const
{
    return typeid(*this).name();
}

