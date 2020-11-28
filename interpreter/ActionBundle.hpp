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
    typedef std::map<std::string, Action> ProtoMap;

    class ActionBundle
    {
    private:
        std::map<int, std::map<std::string, Action>> bundle;
    public:
        static const int UNDEFINED_NUMBER_OF_ARGUMENTS;
        ActionBundle();
        void setAction(Action action);
        void setAction(std::vector<std::string>&& prototype, Action);

    };
    
}



#endif
