#include "Interpreter.hpp"

using namespace std;
using namespace lizzy;


Attributes::Attributes(std::vector<std::string>& tokens)
{
    nparam = -2;
    root = false;
    for(auto attr : tokens)
    {
        if(Parser::isInteger(attr))
        {
            nparam = atoi(attr.c_str());
        }
        else if(attr == "root")
        {
            root = true;
        }
    }
}

int Attributes::getNParam() const
{
    return nparam;
}

bool Attributes::isRoot() const
{
    return root;
}


const int Interpreter::NULL_IPTR = -1;

Interpreter::Interpreter(const std::string& rootPackageName) :
rootPackage(Package::create(rootPackageName)), iptr(NULL_IPTR)
{
    attributeParser.getSeparators().clear();
    attributeParser.getSeparators().push_back(":");
}

Interpreter::~Interpreter()
{
    flushLostResults();
    flushInstructions();
    delete rootPackage;
}

Package& Interpreter::getRootPackage()
{
    return *rootPackage;
}

Parser& Interpreter::getParser()
{
    return parser;
}

const std::vector<LZDataType *>& Interpreter::getLostResults() const
{
    return lostResults;
}

void Interpreter::flushLostResults()
{
    for(LZDataType *data : lostResults)
    {
        if(data)
            delete data;
    }
    lostResults.clear();
}

const std::vector<Instruction *>& Interpreter::getInstructions() const
{
    return instructions;
}

void Interpreter::flushInstructions()
{
    for(Instruction *instr : instructions)
    {
        if(instr)
            delete instr;
    }
    instructions.clear();
}


void Interpreter::parseFile(const std::string& filename)
{
    Debug::loginfo("load file " + filename);
    parse(Parser::load_file(filename));
}

void Interpreter::parse(const std::string& code)
{
    Debug::loginfo("parse");
    parser.parse(code);
    Debug::loginfo("merge");
    parser.merge();
}

void Interpreter::prefetch()
{
    Debug::loginfo("run interpreter");
    vector<string> tokens = parser.getTokens();
    while(tokens.size())
    {
        Debug::loginfo("build new instruction");
        instructions.push_back(buildInstruction(tokens));
        Debug::loginfo("instruction builded: " + instructions.back()->getStackTrace());
    }
}

void Interpreter::execute()
{
    Debug::loginfo("execution...\n\n");
    for(iptr = 0; iptr < instructions.size(); iptr++)
    {
        LZDataType *result = instructions[iptr]->getResult();
        if(result)
            lostResults.push_back(result);
    }
}

Argument *Interpreter::inferSymbol(const std::string& symbol)
{
    Debug::loginfo("infer symbol " + symbol);
    LZDataType *lz = nullptr;
    if(Parser::isString(symbol)) lz = new LZPrimitive<string>(symbol);
    else if(Parser::isBool(symbol)) lz = new LZPrimitive<bool>(symbol == "true");
    else if(Parser::isInteger(symbol)) lz = new LZPrimitive<long>(std::atoi(symbol.c_str()));
    else if(Parser::isFloat(symbol)) lz = new LZPrimitive<double>(std::atof(symbol.c_str()));
    return new Argument(lz);
}

Attributes Interpreter::selectAttributes(std::string& expr)
{
    attributeParser.parse(expr);
    attributeParser.merge();
    expr = attributeParser.getTokens()[0];
    attributeParser.getTokens().erase(attributeParser.getTokens().begin());

    return Attributes(attributeParser.getTokens());
}

Instruction *Interpreter::buildInstruction(Command *command, const Attributes& attribute, vector<string>& tokens)
{
    Debug::loginfo("build instruction with " + command->getViewFullName());
    ActionBundle& actionBundle = command->getActionBundle();
    int nargsGuard = attribute.getNParam() == -2 ? actionBundle.getMin() : attribute.getNParam();
    if(tokens.size() >= nargsGuard || nargsGuard == -2)
    {
        nargsGuard = attribute.getNParam() == -2 ? actionBundle.getMax() : attribute.getNParam();
        Debug::loginfo("arguments: " + to_string(nargsGuard));
        Instruction *instruction = nullptr;
        if(tokens.size() > 0)
        {
            if(not attribute.isRoot())
            {
                string subname = tokens[0];

                Attributes subAttr = selectAttributes(subname);
                Debug::loginfo("search subcommand: " + subname);
                if(command->existsSubCommand(subname))
                {
                    tokens.erase(tokens.begin());
                    Debug::loginfo("subcommand of " + command->getViewFullName() + " detected " + subname);
                    return buildInstruction(command->getSubCommand(subname), subAttr, tokens);
                }
            }
            
            Debug::loginfo(command->getViewFullName() + " is root command");

            instruction = new Instruction(command);

            vector<Command *> occurences;
            
            for(int i = 0; i < nargsGuard; i++)
            {
                string arg = tokens[0];
                tokens.erase(tokens.begin());
                

                if(Parser::isConst(arg))
                {
                    Debug::loginfo("simple constant found: " + arg);
                    instruction->push(inferSymbol(arg));
                }
                else
                {
                    Attributes argAttr = selectAttributes(arg);

                    occurences.clear();

                    Debug::loginfo("search command for " + arg);
                    rootPackage->search(arg, occurences);
                    Command *command = occurences.size() ? occurences.front() : nullptr;
                    
                    if(command)
                    {
                        Debug::loginfo("command found: " + command->getViewFullName());
                        instruction->push(buildInstruction(command, argAttr, tokens));
                    }
                    else
                    {
                        throw LZException("unknown symbol found: " + arg);
                    }
                }
            }
        }
        if(not instruction)
            instruction = new Instruction(command);

        Debug::loginfo("check protoMap for " + to_string(nargsGuard));
        if(actionBundle.existsProtoMap(nargsGuard))
        {
            instruction->setProtoMap(&actionBundle.getProtoMap(nargsGuard));
            return instruction;
        }
        else
        {
            throw LZException(to_string(nargsGuard) + " number of arguments is not available for " + command->getViewFullName() + " command");
        }
    }
    else
    {
        throw LZException(command->getViewFullName() + " has " + to_string(nargsGuard) + " min arguments but instruction has " + to_string(tokens.size()));  
    }
}

Instruction *Interpreter::buildInstruction(vector<string>& tokens)
{
    assert(tokens.size());

    string cmdName = tokens[0];
    tokens.erase(tokens.begin());

    const Attributes& attr = selectAttributes(cmdName);

    Debug::loginfo("search " + cmdName +  " command");

    vector<Command *> occurences;
    rootPackage->search(cmdName, occurences);
    rootPackage->searchExceptionThrowing(cmdName, occurences);
    Command *command = occurences.front();
    return buildInstruction(command, attr, tokens);
}
