#ifndef ACTION_BUNDLE_HPP
#define ACTION_BUNDLE_HPP
#include <vector>
#include <map>
#include <iostream>
#include "DataBuilder.hpp"

namespace lizzy
{
	typedef const std::vector<LZDataType *>& Arguments;
	typedef LZDataType *(*Action)(Arguments);
    typedef std::map<std::string, Action> ProtoMap;

    class ActionBundle
    {
    private:
        std::map<int, ProtoMap> bundle;
    public:
        static const int UNDEFINED_NUMBER_OF_ARGUMENTS;
        ActionBundle();
        void setAction(Action action);
        void setAction(std::vector<std::string>&& prototype, Action);
        ProtoMap& getProtoMap(int nargs);
        bool existsProtoMap(int nargs) const;
        int getMax() const;
        int getMin() const;

    };
    
}



#endif
