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




Interpreter::Interpreter(const std::string& rootPackageName) :
rootPackage(Package::create(rootPackageName))
{
    attributeParser.getSeparators().clear();
    attributeParser.getSeparators().push_back(":");
}

Interpreter::~Interpreter()
{
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

 std::vector<Instruction *> *Interpreter::interpret()
{
    Debug::loginfo("run interpreter");
    vector<Instruction *> *instructions = new vector<Instruction *>();
    vector<string> tokens = parser.getTokens();
    while(tokens.size())
    {
        Debug::loginfo("build new instruction");
        instructions->push_back(buildInstruction(tokens));
        Debug::loginfo("instruction builded: " + instructions->back()->getStackTrace());
    }
    return instructions;
}

Argument *Interpreter::inferConstant(const std::string& symbol)
{
    Debug::loginfo("infer constant " + symbol);
    return new Argument(DataBuilder::build(symbol));
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
    int argsFound = 0;

    if(tokens.size() >= nargsGuard || nargsGuard < 0)
    {
        nargsGuard = attribute.getNParam() == -2 ? actionBundle.getMax() : attribute.getNParam();
        Debug::loginfo("arguments: " + to_string(nargsGuard));
        Instruction *instruction = nullptr;
        if(tokens.size() > 0)
        {
            vector<Command *> occurences;
            //détecter le mode parenthèsé
            /*
            ( => début
            , => break si non parenthèsé
            ) => fin
            ) => fin sans erase() si non parenthèsé
            */
           bool parentheseMode = false;

            for(
            argsFound = 0;
                argsFound < nargsGuard or
                (nargsGuard == -1 and not tokens.empty()) or
                (parentheseMode and not tokens.empty() and tokens[0] != ")");
            argsFound++)
            {
                Debug::logwarn(tokens[0]);
                string arg = tokens[0];

                if(arg == ")" and not parentheseMode)
                    break;

                tokens.erase(tokens.begin());

                if(arg == "(")
                {
                    if(parentheseMode)
                    {
                        throw LZException(command->getFullName() + " has too much '('");
                    }
                    parentheseMode = true;
                    argsFound--;
                    continue;
                }
                else if(arg == ",")
                {
                    if(not parentheseMode) break;
                    argsFound--;
                    continue;
                }
                else if(arg == ")")
                {
                    break;
                }

                if(Parser::isConst(arg))
                {
                    Debug::loginfo("simple constant found: " + arg);
                    if(argsFound == 0) instruction = new Instruction(command);
                    instruction->push(inferConstant(arg));
                }
                else 
                {
                    if(argsFound == 0 and not attribute.isRoot())
                    {
                        string& subname = arg;

                        Attributes subAttr = selectAttributes(subname);
                        Debug::loginfo("search subcommand: " + subname);
                        if(command->existsSubCommand(subname))
                        {
                            Debug::loginfo("subcommand of " + command->getViewFullName() + " detected " + subname);
                            return buildInstruction(command->getSubCommand(subname), subAttr, tokens);
                        }
                    }
                    Attributes argAttr = selectAttributes(arg);

                    occurences.clear();

                    Debug::loginfo("search command for " + arg);
                    rootPackage->search(arg, occurences);
                    Command *command = occurences.size() ? occurences.front() : nullptr;
                    
                    if(command)
                    {
                        if(argsFound == 0) instruction = new Instruction(command);
                        Debug::loginfo("command found: " + command->getViewFullName());
                        instruction->push(buildInstruction(command, argAttr, tokens));
                    }
                    else
                    {
                        throw LZException("unknown symbol found: " + arg);
                    }
                    
                }
            }
            if(parentheseMode and not tokens.empty() and tokens[0] == ")")
                tokens.erase(tokens.begin());
        }
        if(not instruction)
            instruction = new Instruction(command);

        Debug::loginfo("check protoMap for " + to_string(nargsGuard));
        if(actionBundle.existsProtoMap(argsFound))
        {
            instruction->setProtoMap(&actionBundle.getProtoMap(argsFound), nargsGuard == -1);
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
