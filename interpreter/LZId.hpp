#ifndef LZ_ID_HPP
#define LZ_ID_HPP
#include "LZPrimitive.hpp"
#include "Parser.hpp"


namespace lizzy
{
    class LZId : public LZPrimitive<std::string>
    {
    public:
        static const std::string type;
        LZId();
        LZId(const std::string& value);
        virtual ~LZId();
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
