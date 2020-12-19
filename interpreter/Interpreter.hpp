#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include "Package.hpp"
#include "Parser.hpp"
#include "Instruction.hpp"
#include "DataBuilder.hpp"
#include "Executer.hpp"
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
        Attributes selectAttributes(std::string& expr);
        Instruction *buildInstruction(std::vector<std::string>& tokens);
        Instruction *buildInstruction(Command *command, const Attributes& attr, std::vector<std::string>& tokens);
        Argument *inferConstant(const std::string& symbol);
        Argument *inferIdentifier(const std::string& symbol);
    public:
        Interpreter(const std::string& rootPackageName="root");
        virtual ~Interpreter();
        Package& getRootPackage();
        Parser& getParser();
        void parseFile(const std::string& filename);
        void parse(const std::string& code);
        Executer *interpret();
    };
}


#endif
