//#include "Parser.hpp"
//#include "Package.hpp"
#include <map>
#include <iostream>
#include <type_traits>
#include <functional>
#include "Interpreter.hpp"
#include "Debug.hpp"
#include "LizzyApi.hpp"

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
    try
    {
        Interpreter interpreter;



        lizzy::api::connect_api(interpreter.getRootPackage().createPackage("__custom_api__"));
        
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
