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
    private:
        void *value;
    public:
        LZDataType();
        LZDataType(void *ptr);
        virtual ~LZDataType();
        virtual std::string getId() const final;
        void *getValue() const;
        void setValue(void *value);
        std::string toString();
    };
}


#endif
