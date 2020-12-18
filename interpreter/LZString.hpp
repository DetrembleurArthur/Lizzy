#ifndef LZ_STRING_HPP
#define LZ_STRING_HPP
#include "LZPrimitive.hpp"
#include "Parser.hpp"


namespace lizzy
{
    class LZString : public LZPrimitive<std::string>
    {
    public:
        static const std::string type;
        LZString();
        LZString(const std::string& value);
        LZString(const LZString& value);
        virtual ~LZString();
        virtual std::string getId() const override;
        std::string toString() override;
        long toInt() override;
        double toFloat() override;
        bool toBool() override;
        void setValue(std::string value) override;
        void setFromString(const std::string& value) override;
    };
}


#endif
