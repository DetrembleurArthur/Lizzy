#ifndef LZ_BOOL_HPP
#define LZ_BOOL_HPP
#include "LZPrimitive.hpp"


namespace lizzy
{
    class LZBool : public LZPrimitive<bool>
    {
    public:
        static const std::string type;
        LZBool();
        LZBool(bool value);
        LZBool(const std::string& value);
        LZBool(const LZBool& value);
        virtual ~LZBool();
        std::string toString() override;
        long toInt() override;
        double toFloat() override;
        bool toBool() override;
        void setFromString(const std::string& value) override;
    };
}


#endif
