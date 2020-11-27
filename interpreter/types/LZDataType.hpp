#ifndef LZ_DATA_TYPE_HPP
#define LZ_DATA_TYPE_HPP
#include <string>

namespace lizzy
{
    class LZDataType
    {
    private:
        void *value;
    public:
        LZDataType();
        LZDataType();
        virtual std::string getName() const;
    };
}


#endif
