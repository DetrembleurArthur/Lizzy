#ifndef LZ_DATA_TYPE_HPP
#define LZ_DATA_TYPE_HPP
#include <type_traits>
#include <functional>
#include "Debug.hpp"
#include "Exceptions.hpp"

#define ID(type) typeid(type).name()

namespace lizzy
{
    class LZDataType
    {
    public:
        static const std::string type;
        LZDataType();
        virtual ~LZDataType();
        virtual std::string getId() const;
        virtual size_t getHashCode() const final;
        virtual std::string toString();
        virtual long toInt();
        virtual double toFloat();
        virtual bool toBool();
        template <class LZ> operator LZ*()
        {
            return dynamic_cast<LZ *>(this);
        }
        static int isDataType(LZDataType *other);
        static int isInteger(LZDataType *other);
        static int isFloat(LZDataType *other);
        static int isBool(LZDataType *other);
        static int isString(LZDataType *other);
        static int isId(LZDataType *other);
    };
}


#endif
