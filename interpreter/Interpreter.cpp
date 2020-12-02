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
    cout << "ATTR{" << nparam << ", " << root << "}" << endl;
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
    parse(Parser::load_file(filename));
}

void Interpreter::parse(const std::string& code)
{
    parser.parse(code);
    parser.merge();
}

void Interpreter::run()
{
    vector<string> tokens = parser.getTokens();
    while(tokens.size())
    {
        instructions.push_back(buildInstruction(tokens));
    }
}

Argument *Interpreter::inferSymbol(const std::string& symbol)
{
    cout << "infer symbol " << symbol << endl;
    return (Argument *)nullptr;
}

Attributes Interpreter::selectAttributes(std::string& expr)
{
    attributeParser.parse(expr);
    attributeParser.merge();
    expr = attributeParser.getTokens()[0];
    attributeParser.getTokens().erase(attributeParser.getTokens().begin());

    return Attributes(attributeParser.getTokens());
}

Instruction *Interpreter::buildInstruction(Command& command, const Attributes& attribute, vector<string>& tokens)
{
    cerr << "BEG INSTRUCTION"<<endl;
    ActionBundle& actionBundle = command.getActionBundle();
    int nargsGuard = attribute.getNParam() == -2 ? actionBundle.getMin() : attribute.getNParam();
    if(tokens.size() >= nargsGuard)
    {
        nargsGuard = attribute.getNParam() == -2 ? actionBundle.getMax() : attribute.getNParam();
        cout << "ARGS: " << nargsGuard << endl;
        Instruction *instruction = nullptr;
        if(tokens.size() > 0)
        {
            if(not attribute.isRoot())
            {
                string subname = tokens[0];

                Attributes subAttr = selectAttributes(subname);
                if(command.existsSubCommand(subname))
                {
                    tokens.erase(tokens.begin());
                    return buildInstruction(command.getSubCommand(subname), subAttr, tokens);
                }
            }
            
            instruction = new Instruction(command);
            for(int i = 0; i < nargsGuard; i++, tokens.erase(tokens.begin()))
            {
                string arg = tokens[0];
                Attributes argAttr = selectAttributes(arg);
                if(rootPackage->existsCommand(arg))
                {
                    instruction->push(buildInstruction(rootPackage->getCommand(arg), argAttr, tokens));
                }
                else
                {
                    instruction->push(inferSymbol(arg));
                }
            }
        }
        if(not instruction)
            instruction = new Instruction(command);
        if(actionBundle.existsProtoMap(nargsGuard))
        {
            cout << "instruction builded" << endl;
            instruction->setProtoMap(&actionBundle.getProtoMap(nargsGuard));
            return instruction;
        }
        else
        {
            throw LZException(to_string(nargsGuard) + " number of arguments is not available for " + command.getViewFullName() + " command");
        }
    }
    else
    {
        throw LZException(command.getViewFullName() + " has " + to_string(nargsGuard) + " min arguments but instruction has " + to_string(tokens.size()));  
    }
}

Instruction *Interpreter::buildInstruction(vector<string>& tokens)
{
    assert(tokens.size());

    string cmdName = tokens[0];
    tokens.erase(tokens.begin());

    const Attributes& attr = selectAttributes(cmdName);

    cout << "COMMAND: " << cmdName << endl;

    Command& command = rootPackage->getCommand(cmdName);
    return buildInstruction(command, attr, tokens);
}
