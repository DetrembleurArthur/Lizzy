#ifndef ACTION_BUNDLE_HPP
#define ACTION_BUNDLE_HPP
#include <vector>
#include <map>
#include <iostream>
#include "types/LZDataType.hpp"

namespace lizzy
{
	typedef const std::vector<LZDataType *>& Arguments;
	typedef LZDataType *(*Action)(Arguments);

    class ActionBundle
    {
    private:
        std::map<std::string, Action> bundle;
    public:
        ActionBundle();
        void setAction(std::vector<std::string>&& prototype, Action);

    };
    
}



#endif
