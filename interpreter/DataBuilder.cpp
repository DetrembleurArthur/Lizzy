#include "DataBuilder.hpp"


using namespace std;
using namespace lizzy;



LZDataType *DataBuilder::build(string expr, bool strExplicit)
{
    LZDataType *data = nullptr;
    if(Parser::isString(expr))
    {
        if(not strExplicit)
        {
            expr = "\"" + expr + "\"";
        }
        data = buildString(expr);
    }
    else if(Parser::isBool(expr))
    {
        data = buildBool(expr);
    }
    else if(Parser::isInteger(expr))
    {
        data = buildInteger(expr);
    }
    else if(Parser::isFloat(expr))
    {
        data = buildFloat(expr);
    }
    else if(not strExplicit)
    {
        expr = "\"" + expr + "\"";
        data = buildString(expr);
    }
    if(data) return data;
    throw LZException("\"" + expr + "\" is not a primitive value");
}

LZId *DataBuilder::buildId(const std::string& expr)
{
    return new LZId(expr);
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

LZVariable *DataBuilder::buildVariable(const std::string& expr)
{
    return new LZVariable(expr);
}
