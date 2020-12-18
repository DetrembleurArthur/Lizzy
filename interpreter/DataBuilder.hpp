#ifndef DATA_BUILDER_HPP
#define DATA_BUILDER_HPP
#include "LZInteger.hpp"
#include "LZFloat.hpp"
#include "LZBool.hpp"
#include "LZString.hpp"
#include "LZVariable.hpp"
#include "LZId.hpp"
#include <unordered_map>



namespace lizzy
{
    class DataBuilder
    {
    public:
        static LZDataType *build(std::string expr, bool strExplicit=true);
        static LZId *buildId(const std::string& expr);
        static LZInteger *buildInteger(const std::string& expr);
        static LZFloat *buildFloat(const std::string& expr);
        static LZBool *buildBool(const std::string& expr);
        static LZString *buildString(const std::string& expr);
        static LZVariable *buildVariable(const std::string& expr);
    };
}




#endif
