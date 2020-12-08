#ifndef EXECUTER_HPP
#define EXECUTER_HPP
#include "Instruction.hpp"


namespace lizzy
{
    class Executer
    {
    private:
        std::vector<Instruction *> *instructions;
        std::vector<LZDataType *> lostResults;
        int iptr;
    public:
        Executer();
        virtual ~Executer();
        void setInstructions(std::vector<Instruction *> *instructions);
        void execute();
        std::vector<LZDataType *>& getLostResults();
    };
}



#endif
