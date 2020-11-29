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
        Package *package = Package::create();
        package->createPackage("lizzy").createCommand("load.file");
        package->getPackage("lizzy").createCommand("hello");
        package->createPackage("user").createCommand("hostname");

        delete package;
    }
    catch(const LZException& e)
    {
        cout << e.getMessage() << endl;
    }

    
    return 0;
}
