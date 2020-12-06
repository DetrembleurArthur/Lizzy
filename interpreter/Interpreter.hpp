#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "Package.hpp"
#include "Parser.hpp"
#include "Instruction.hpp"
#include "DataBuilder.hpp"
#include <assert.h>


namespace lizzy
{
    struct Attributes
    {
        int nparam;
        bool root;
        Attributes(std::vector<std::string>& tokens);
        int getNParam() const;
        bool isRoot() const;
    };

    class Interpreter
    {
    private:
        Package *rootPackage;
        Parser parser;
        Parser attributeParser;
        std::vector<LZDataType *> lostResults;
        std::vector<Instruction *> instructions;
        int iptr;
        Attributes selectAttributes(std::string& expr);
        Instruction *buildInstruction(std::vector<std::string>& tokens);
        Instruction *buildInstruction(Command *command, const Attributes& attr, std::vector<std::string>& tokens);
        Argument *inferConstant(const std::string& symbol);
    public:
        static const int NULL_IPTR;
        Interpreter(const std::string& rootPackageName="lizzy");
        virtual ~Interpreter();
        Package& getRootPackage();
        Parser& getParser();
        void parseFile(const std::string& filename);
        void parse(const std::string& code);
        void execute();
        void prefetch();
        const std::vector<LZDataType *>& getLostResults() const;
        void flushLostResults();
        const std::vector<Instruction *>& getInstructions() const;
        void flushInstructions();
    };
}


#endif
