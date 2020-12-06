//#include "Parser.hpp"
//#include "Package.hpp"
#include <map>
#include <iostream>
#include <type_traits>
#include <functional>
#include "Interpreter.hpp"
#include "Debug.hpp"
#include "types/LZPrimitive.hpp"

using namespace std;
using namespace lizzy;



namespace api
{
    LZDataType *print(Arguments args)
    {
        LZPrimitive<string> *msg = *args[0];
        LZPrimitive<double> *l = *args[1];
        cout << msg->getValue() << " " << l->getValue() << endl;
        return (LZDataType *)nullptr;
    }
}


int main(int argc, char const *argv[])
{
    LZDataType *p = new LZFloat("3.66");
    cout << p->getId() << endl;
    try
    {
        Interpreter interpreter;
        interpreter.getRootPackage().createPackage("std.io");
        interpreter.getRootPackage().createPackage("user.custom");
        interpreter.getRootPackage().createPackage("user.func");
        interpreter.getRootPackage().getPackage("std.io")->createCommand("print")
        .getActionBundle().setAction({typeid(LZString).name(), typeid(LZFloat).name()}, api::print);

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
