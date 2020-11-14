#include "Parser.hpp"

using namespace std;
using namespace lizzy;


int main(int argc, char const *argv[])
{
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

    return 0;
}
