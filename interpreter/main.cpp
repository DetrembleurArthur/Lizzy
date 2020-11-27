//#include "Parser.hpp"
//#include "Package.hpp"
#include <map>
#include <iostream>
#include <type_traits>
#include "ActionBundle.hpp"

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
    ActionBundle bundle;


    LZDataType lz;

    class LZ2 : public LZDataType
    {};
    LZ2 lz2;

    LZDataType *plz = &lz2;

    LZDataType& rlz = lz2;

    bundle.setAction({plz->getId()}, [](Arguments args)
    {
        LZDataType& d = *args[0];

        return new LZDataType();
    });
    
    return 0;
}
