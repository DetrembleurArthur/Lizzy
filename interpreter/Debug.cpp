#include "Debug.hpp"

using namespace std;
using namespace lizzy;


void Debug::loginfo(const string& msg)
{
    cout << "\033[96m[INFO]\033[0m " << msg << endl;
}

void Debug::logerr(const string& msg)
{
    cout << "\033[91m[ERROR]\033[0m " << msg << endl;
}

void Debug::logwarn(const string& msg)
{
    cout << "\033[95m[WARNING]\033[0m " << msg << endl;
}

void Debug::logfatal(const string& msg)
{
    cout << "\033[91;1;5;4;6m[FATAL]\033[0m " << msg << endl;
}
