#ifndef LZ_FLOAT_HPP
#define LZ_FLOAT_HPP
#include "LZPrimitive.hpp"


namespace lizzy
{
    class LZFloat : public LZPrimitive<double>
    {
    public:
        static const std::string type;
        LZFloat();
        LZFloat(double value);
        LZFloat(const std::string& value);
        LZFloat(const LZFloat& value);
        virtual ~LZFloat();
        virtual std::string getId() const override;
        std::string toString() override;
        long toInt() override;
        double toFloat() override;
        bool toBool() override;
        void setFromString(const std::string& value) override;
    };
}


#endif
