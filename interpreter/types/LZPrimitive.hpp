#ifndef LZ_PRIMITIVE_HPP
#define LZ_PRIMITIVE_HPP
#include "LZDataType.hpp"
#include "../Parser.hpp"


namespace lizzy
{
    template <typename T> class LZPrimitive : public LZDataType
    {
    private:
        T value;
    public:
        LZPrimitive();
        LZPrimitive(T value);
        LZPrimitive(const LZPrimitive<T>& value);
        virtual ~LZPrimitive();
        T getValue() const;
        virtual void setValue(T value);
        virtual void setFromString(const std::string& value);
    };
}


#endif
