#ifndef LZ_INTEGER_HPP
#define LZ_INTEGER_HPP
#include "LZPrimitive.hpp"


namespace lizzy
{
    class LZInteger : public LZPrimitive<long>
    {
    public:
        static const std::string type;
        LZInteger();
        LZInteger(long value);
        LZInteger(const std::string& value);
        LZInteger(const LZInteger& value);
        virtual ~LZInteger();
        std::string toString() override;
        long toInt() override;
        double toFloat() override;
        bool toBool() override;
        void setFromString(const std::string& value) override;
    };
}


#endif
