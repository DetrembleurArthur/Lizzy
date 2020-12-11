#include "DataBuilder.hpp"


using namespace std;
using namespace lizzy;



std::unordered_map<std::string, LZDataType *> DataBuilder::constants = std::unordered_map<std::string, LZDataType *>();


LZDataType *DataBuilder::build(string expr, bool strExplicit)
{
    LZDataType *data = nullptr;
    if(constants.find(expr) != constants.end() and strExplicit)
        return constants[expr];
    if(Parser::isString(expr))
    {
        if(not strExplicit)
        {
            expr = "\"" + expr + "\"";
            if(constants.find(expr) != constants.end())
                return constants[expr];
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
        if(constants.find(expr) != constants.end())
            return constants[expr];
        data = buildString(expr);
    }
    if(data)
    {
        Debug::logwarn("const: " + expr);
        constants[expr] = data;
        return data;
    }
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

LZInteger *DataBuilder::rbuildInteger(int expr)
{
    std::string str = to_string(expr);
    if(constants.find(str) != constants.end())
        return dynamic_cast<LZInteger *>(constants[str]);
    LZInteger *data = new LZInteger(expr);
    constants[str] = data;
    return data;
}

LZFloat *DataBuilder::rbuildFloat(double expr)
{
    std::string str = to_string(expr);
    if(constants.find(str) != constants.end())
        return dynamic_cast<LZFloat *>(constants[str]);
    LZFloat *data = new LZFloat(expr);
    constants[str] = data;
    return data;
}

LZBool *DataBuilder::rbuildBool(bool expr)
{
    std::string str = expr ? "true" : "false";
    if(constants.find(str) != constants.end())
        return dynamic_cast<LZBool *>(constants[str]);
    LZBool *data = new LZBool(expr);
    constants[str] = data;
    return data;
}

LZString *DataBuilder::rbuildString(std::string expr, bool strExplicit)
{
    if(not strExplicit)
        expr = "\"" + expr + "\"";
    if(constants.find(expr) != constants.end())
        return dynamic_cast<LZString *>(constants[expr]);
    LZString *data = new LZString(expr);
    constants[expr] = data;
    return data;
}

void DataBuilder::clearConstants()
{
    for(auto it = constants.begin(); it != constants.end(); it++)
    {
        delete it->second;
    }
}
