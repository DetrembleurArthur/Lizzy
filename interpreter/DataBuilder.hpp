#ifndef DATA_BUILDER_HPP
#define DATA_BUILDER_HPP
#include "LZInteger.hpp"
#include "LZFloat.hpp"
#include "LZBool.hpp"
#include "LZString.hpp"
#include <unordered_map>



namespace lizzy
{
    class DataBuilder
    {
    private:
        static std::unordered_map<std::string, LZDataType *> constants;
    public:
        static LZDataType *build(std::string expr, bool strExplicit=true);
        static LZInteger *buildInteger(const std::string& expr);
        static LZFloat *buildFloat(const std::string& expr);
        static LZBool *buildBool(const std::string& expr);
        static LZString *buildString(const std::string& expr);
        static LZInteger *rbuildInteger(int expr);
        static LZFloat *rbuildFloat(double expr);
        static LZBool *rbuildBool(bool expr);
        static LZString *rbuildString(std::string expr, bool strExplicit=true);
        static void clearConstants();
    };
}




#endif
