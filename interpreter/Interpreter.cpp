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

 Executer *Interpreter::interpret()
{
    Debug::loginfo("run interpreter");
    vector<Instruction *> *instructions = new vector<Instruction *>();
    BranchController *branchController = new BranchController();
    vector<string> tokens = parser.getTokens();
    while(tokens.size())
    {
        Debug::loginfo("build new instruction");
        Instruction *instruction = buildInstruction(tokens);
        branchController->build(instructions->size(), instruction->getCommand()->getFullName());
        instructions->push_back(instruction);
        Debug::loginfo("instruction builded: " + instructions->back()->getStackTrace());
    }
    Executer *executer = new Executer();
    branchController->finalize();
    branchController->show();

    ExecutionEnv *env = new ExecutionEnv();
    env->setBranchController(branchController);
    env->setInstructions(instructions);
    env->setDataStack(DataStack::create());
    executer->setEnv(env);
    return executer;
}

Argument *Interpreter::inferConstant(const std::string& symbol)
{
    Debug::loginfo("infer constant " + symbol);
    return new Argument(DataBuilder::build(symbol));
}

Argument *Interpreter::inferIdentifier(const std::string& symbol)
{
    Debug::loginfo("infer constant " + symbol);
    return new Argument(DataBuilder::buildId(symbol));
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
    auto len = parser.size(tokens);

    if(len >= nargsGuard || nargsGuard < 0)
    {
        nargsGuard = attribute.getNParam() == -2 ? actionBundle.getMax() : attribute.getNParam();
        Debug::loginfo("arguments: " + to_string(nargsGuard));
        Instruction *instruction = nullptr;
        if(tokens.size() > 0)
        {
            vector<Command *> occurences;
            if(tokens[0] != "()")
            {
                if(argsFound == 0 and not attribute.isRoot())
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
                bool parentheseMode = false;
                for(
                argsFound = 0;
                    (argsFound == 0 and tokens[0] == "(") or //parenthèsé à 0 argument mais avec une liste éronnée d'arguments
                    argsFound < nargsGuard or //cas classique
                    (nargsGuard == -1 and not tokens.empty()) or //cas d'une command à nombre d'arguments indéfini
                    (parentheseMode and not tokens.empty()); //cas parenthèsé supposé correct
                argsFound++)
                {
                    string arg = tokens[0];
                    Debug::logwarn(arg);

                    tokens.erase(tokens.begin());

                    if(arg == "(")
                    {
                        if(parentheseMode == true)
                            throw LZException("too much '(' for " + command->getViewFullName());
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
                        parentheseMode = false;
                        break;
                    }

                    if(Parser::isConst(arg))
                    {
                        Debug::loginfo("simple constant found: " + arg);
                        if(argsFound == 0) instruction = new Instruction(command);
                        instruction->push(inferConstant(arg));
                    }
                    else if(Parser::isIdentifier(arg))
                    {
                        Debug::loginfo("simple id found: " + arg);
                        if(argsFound == 0) instruction = new Instruction(command);
                        instruction->push(inferIdentifier(arg));
                    }
                    else
                    {
                        
                        Attributes argAttr = selectAttributes(arg);

                        occurences.clear();

                        Debug::loginfo("search command for " + arg);
                        rootPackage->search(arg, occurences);
                        Command *argCommand = occurences.size() ? occurences.front() : nullptr;
                        
                        if(argCommand)
                        {
                            if(argsFound == 0) instruction = new Instruction(command);
                            Debug::loginfo("command found: " + argCommand->getViewFullName());
                            instruction->push(buildInstruction(argCommand, argAttr, tokens));
                        }
                        else
                        {
                            throw LZException("unknown symbol found: " + arg);
                        }
                    }
                }
            }
            else
            {
                tokens.erase(tokens.begin());
            }
            
        }
        if(not instruction)
            instruction = new Instruction(command);

        Debug::loginfo("check protoMap for " + to_string(nargsGuard));
        if(actionBundle.existsPrototype(argsFound))
        {
            instruction->setPrototype(&actionBundle.getPrototype(argsFound), nargsGuard == -1);
            return instruction;
        }
        else
        {
            throw LZException(to_string(argsFound) + " number of arguments is not available for " + command->getViewFullName() + " command");
        }
    }
    else
    {
        throw LZException(command->getViewFullName() + " has " + to_string(nargsGuard) + " min arguments but instruction has " + to_string(len));  
    }
}

Instruction *Interpreter::buildInstruction(vector<string>& tokens)
{
    assert(tokens.size());

    string cmdName = tokens[0];
    tokens.erase(tokens.begin());

    if(Parser::isConst(cmdName))
        throw LZException("'" + cmdName + "' constant must be in a command expression");

    const Attributes& attr = selectAttributes(cmdName);

    Debug::loginfo("search " + cmdName +  " command");

    vector<Command *> occurences;
    rootPackage->search(cmdName, occurences);
    rootPackage->searchExceptionThrowing(cmdName, occurences);
    Command *command = occurences.front();
    return buildInstruction(command, attr, tokens);
}
