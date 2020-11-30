#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "Package.hpp"
#include "Parser.hpp"
#include "Instruction.hpp"


namespace lizzy
{
    class Interpreter
    {
    private:
        Package *rootPackage;
        Parser parser;
        std::vector<LZDataType *> lostResults;
        std::vector<Instruction *> instructions;
        int iptr;
    public:
        Interpreter(const std::string rootPackageName="lizzy");
        virtual ~Interpreter();
        Package& getRootPackage();
        Parser& getParser();
        void run();
        const std::vector<LZDataType *>& getLostResults() const;
        void flushLostResults();
        const std::vector<Instruction *>& getInstructions() const;
        void flushInstructions();
    };
}


#endif
