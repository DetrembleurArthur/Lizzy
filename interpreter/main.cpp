//#include "Parser.hpp"
//#include "Package.hpp"
#include <map>
#include <iostream>
#include <type_traits>
#include "Package.hpp"

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
        Command command("print");
        command.createSubCommand("integer.time");
        command.createSubCommand("integer.one");
        command.createSubCommand("float.time");
cout << "!" <<endl;
        command.removeSubCommand("integer.one");
cout << "!" << endl;
     //   package.createCommand("std.math.mul");
    }
    catch(const LZException& e)
    {
        cout << e.getMessage() << endl;
    }

    
    return 0;
}
