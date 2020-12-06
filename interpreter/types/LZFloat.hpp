#ifndef LZ_FLOAT_HPP
#define LZ_FLOAT_HPP
#include "LZPrimitive.hpp"


namespace lizzy
{
    class LZFloat : public LZPrimitive<double>
    {
    public:
        LZFloat();
        LZFloat(double value);
        LZFloat(const std::string& value);
        LZFloat(const LZFloat& value);
        virtual ~LZFloat();
        std::string toString() override;
        long toInt() override;
        double toFloat() override;
        bool toBool() override;
        void setFromString(const std::string& value) override;
    };
}


#endif
