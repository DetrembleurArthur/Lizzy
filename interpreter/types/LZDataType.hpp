#ifndef LZ_DATA_TYPE_HPP
#define LZ_DATA_TYPE_HPP
#include <type_traits>
#include "../Debug.hpp"
#include "../Exceptions.hpp"

#define ID(type) typeid(type).name()

namespace lizzy
{
    class LZDataType
    {
    public:
        LZDataType();
        virtual ~LZDataType();
        virtual std::string getId() const final;
        virtual std::string toString();
        virtual int toInt();
        virtual double toFloat();
        virtual bool toBool();
        template <class LZ> operator LZ*()
        {
            return dynamic_cast<LZ *>(this);
        }
    };
}


#endif
