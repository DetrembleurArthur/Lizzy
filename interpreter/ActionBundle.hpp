#ifndef ACTION_BUNDLE_HPP
#define ACTION_BUNDLE_HPP
#include <vector>
#include <map>
#include <iostream>
#include "DataBuilder.hpp"
#include "ExecutionEnv.hpp"

namespace lizzy
{
	typedef const std::vector<LZDataType *>& Arguments;
	typedef LZDataType *(*Action)(Arguments, ExecutionEnv *);

    class Prototype
    {
    private:
        int nargs = -2;
        std::vector<std::vector<int (*)(LZDataType *)>> conditions;
        std::vector<Action> actions;
    public:
        void setArgs(int n);
        void set(std::vector<int (*)(LZDataType *)>& condition, Action action);
        void set(Action action);
        Action get(std::vector<LZDataType *>& data);
    };

    class ActionBundle
    {
    private:
        std::map<int, Prototype> bundle;
    public:
        static const int UNDEFINED_NUMBER_OF_ARGUMENTS;
        ActionBundle();
        void setAction(Action action);
        void setAction(std::vector<int (*)(LZDataType *)>&& condition, Action action);
        Prototype& getPrototype(int nargs);
        bool existsPrototype(int nargs) const;
        int getMax() const;
        int getMin() const;

    };
    
}



#endif
