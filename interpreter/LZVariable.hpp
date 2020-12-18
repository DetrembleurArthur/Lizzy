#ifndef LZ_VARIABLE_HPP
#define LZ_VARIABLE_HPP
#include "LZDataType.hpp"


namespace lizzy
{
    class LZVariable : public LZDataType
    {
    private:
        std::string name;
        LZDataType *reference;
    public:
        LZVariable(const std::string& name);
        LZVariable(const std::string& name, LZDataType *other);
        virtual ~LZVariable();
        virtual std::string getId() const override;
        LZDataType *getValue();
        void setValue(LZDataType *reference);
        bool isNull() const;
        std::string toString() override;
        long toInt() override;
        double toFloat() override;
        bool toBool() override;
        std::string getName() const;
    };
}


#endif
