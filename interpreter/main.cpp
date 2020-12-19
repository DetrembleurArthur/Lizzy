//#include "Parser.hpp"
//#include "Package.hpp"
#include <map>
#include <iostream>
#include <type_traits>
#include <functional>
#include "Interpreter.hpp"
#include "Debug.hpp"
#include "LizzyApi.hpp"
#include "Executer.hpp"

using namespace std;
using namespace lizzy;


int main(int argc, char const *argv[])
{
    try
    {
        Interpreter interpreter;
        Executer *executer;

        lizzy::api::connect_api(interpreter.getRootPackage().createPackage("__custom_api__"));
        
        interpreter.parseFile("main.lz");

        executer = interpreter.interpret();

        executer->execute();

        delete executer;
        
    }
    catch(const LZException& e)
    {
        Debug::logerr(e.getMessage());
    }

    
    return 0;
}
