#include "DataBuilder.hpp"


using namespace std;
using namespace lizzy;


LZDataType *DataBuilder::build(const string& expr, bool strExplicit)
{
    if(Parser::isString(expr))
    {
        if(not strExplicit)
            return buildString("\"" + expr + "\"");
        return buildString(expr);
    }
    if(Parser::isBool(expr))
    {
        return buildBool(expr);
    }
    if(Parser::isInteger(expr))
    {
        return buildInteger(expr);
    }
    if(Parser::isFloat(expr))
    {
        return buildFloat(expr);
    }
    if(not strExplicit)
        return buildString("\"" + expr + "\"");
    throw LZException("\"" + expr + "\" is not a primitive value");
}

LZInteger *DataBuilder::buildInteger(const std::string& expr)
{
    return new LZInteger(expr);
}

LZFloat *DataBuilder::buildFloat(const std::string& expr)
{
    return new LZFloat(expr);
}

LZBool *DataBuilder::buildBool(const std::string& expr)
{
    return new LZBool(expr);
}

LZString *DataBuilder::buildString(const std::string& expr)
{
    return new LZString(expr);
}
