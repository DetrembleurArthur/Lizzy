#ifndef ACTION_BUNDLE_HPP
#define ACTION_BUNDLE_HPP
#include <vector>
#include <map>
#include "types/LZDataType.hpp"

namespace lizzy
{
    class ActionBundle
    {
    private:
        std::map<std::string, LZDataType (*)(const std::vector<LZDataType&&>&)> bundle;
    public:
        ActionBundle();
        void setAction(std::vector<std::string&&>&& prototype, LZDataType (*f)(const std::vector<LZDataType&&>&));
    };
    
}



#endif
