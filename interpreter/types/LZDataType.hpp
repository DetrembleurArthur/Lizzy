#ifndef LZ_DATA_TYPE_HPP
#define LZ_DATA_TYPE_HPP
#include <string>
#include <type_traits>
#define ID(type) typeid(type).name()

namespace lizzy
{
    class LZDataType
    {
    private:
        void *value;
    public:
        LZDataType();
        virtual std::string getId() const final;
    };
}


#endif
