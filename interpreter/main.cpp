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
        Package package("root.master");
        package.addPackage("std.math");
        package.addPackage("std.io");
        package.addPackage("std.str");
        package.addPackage("user.func");
        cout << package.existsPackage("std.io") << endl;
        package.removePackage("std.io");
        cout << package.existsPackage("std.io") << endl;
    }
    catch(const LZException& e)
    {
        cout << e.getMessage() << endl;
    }

    
    return 0;
}
