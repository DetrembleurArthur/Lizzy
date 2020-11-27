#include "ActionBundle.hpp"


using namespace std;
using namespace lizzy;

ActionBundle::ActionBundle()
{
	
}

void ActionBundle::setAction(vector<string>&& prototype, Action action)
{
    string proto_str = "";
    if(not prototype.empty())
    {
        proto_str = prototype[0];
        auto len = prototype.size();
        for(int i = 1; i < len; i++)
        {
            proto_str += "-" + prototype[i];
        }
    }
    cout << proto_str << endl;
    bundle[proto_str] = action;
}
