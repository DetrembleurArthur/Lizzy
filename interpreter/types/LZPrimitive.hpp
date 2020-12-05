#ifndef LZ_PRIMITIVE_HPP
#define LZ_PRIMITIVE_HPP
#include "LZDataType.hpp"

#define ID(type) typeid(type).name()

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
        void setValue(T value);
    };
}


#endif
