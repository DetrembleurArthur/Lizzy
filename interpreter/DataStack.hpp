#ifndef DATA_STACK_HPP
#define DATA_STACK_HPP
#include <vector>
#include <stack>
#include "LZVariable.hpp"
#include "Parser.hpp"


namespace lizzy
{
    class DataStack
    {
    private:
        std::vector<LZVariable *> stack;
        std::stack<long> contextPointers;
        DataStack();
    public:
        virtual ~DataStack();
        static DataStack *create();
        int push(LZVariable *var);
        void push();
        void pop();
        size_t variables() const;
        size_t contexts() const;
        LZVariable *getVariable(const std::string& id);
    };
}


#endif

