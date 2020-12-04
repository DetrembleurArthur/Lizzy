//#include "Parser.hpp"
//#include "Package.hpp"
#include <map>
#include <iostream>
#include <type_traits>
#include "Interpreter.hpp"
#include "Debug.hpp"

using namespace std;
using namespace lizzy;



namespace api
{
    LZDataType *print(Arguments args)
    {
        for(auto *lz : args)
        {
            cout << lz->toString() << endl;
        }
        return (LZDataType *)nullptr;
    }
}


int main(int argc, char const *argv[])
{
    try
    {
        Interpreter interpreter;
        interpreter.getRootPackage().createPackage("std.io");
        interpreter.getRootPackage().createPackage("user.custom");
        interpreter.getRootPackage().createPackage("user.func");
        interpreter.getRootPackage().getPackage("std.io")->createCommand("print")
        .getActionBundle().setAction({typeid(LZDataType).name(), typeid(LZDataType).name()}, api::print);

        interpreter.parseFile("main.lz");

        interpreter.prefetch();

        interpreter.execute();
        
    }
    catch(const LZException& e)
    {
        Debug::logerr(e.getMessage());
    }

    
    return 0;
}
