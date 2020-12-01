//#include "Parser.hpp"
//#include "Package.hpp"
#include <map>
#include <iostream>
#include <type_traits>
#include "Package.hpp"
#include "Instruction.hpp"

using namespace std;
using namespace lizzy;


int main(int argc, char const *argv[])
{/*
    Parser parser;
    parser.parse(Parser::load_file("main.lz"));


    for(const auto& token : parser.getTokens())
    {
        cout << "> " << token << endl;
    }

    cout << "########" << endl;
    parser.merge();

    for(const auto& token : parser.getTokens())
    {
        cout << "> " << token << endl;
    }
*/
    try
    {
        Package *package = Package::create();
        
        package->createCommand("print.hello").getActionBundle().setAction({typeid(LZDataType).name()}, [](Arguments args){
            cout << "Hello world! " << args.size() << endl;
            return (LZDataType *)nullptr;
        });

        auto& cmd = package->getCommand("print.hello");
        Instruction *instr = new Instruction(cmd, cmd.getActionBundle().getProtoMap(1));
        LZDataType *data = new LZDataType();
        Argument *arg = new Argument(data);

        instr->push(arg);
        
        instr->getResult();

        delete arg;

        delete data;
        
        delete instr;

        delete package;
    }
    catch(const LZException& e)
    {
        cout << e.getMessage() << endl;
    }

    
    return 0;
}
