//#include "Parser.hpp"
//#include "Package.hpp"
#include <map>
#include <iostream>
#include <type_traits>
#include "Interpreter.hpp"
#include "Debug.hpp"

using namespace std;
using namespace lizzy;


int main(int argc, char const *argv[])
{
    try
    {
        Interpreter interpreter;
        interpreter.getRootPackage().createPackage("test.cmd")
        .createCommand("add").getActionBundle().setAction({typeid(LZDataType).name()}, [](Arguments)
        {
            return (LZDataType *)nullptr;
        });

        interpreter.parseFile("main.lz");

        interpreter.run();
        
    }
    catch(const LZException& e)
    {
        cout << "ERR: " << e.getMessage() << endl;
    }

    
    return 0;
}
