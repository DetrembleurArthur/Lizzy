#include "ActionBundle.hpp"


using namespace std;
using namespace lizzy;

const int ActionBundle::UNDEFINED_NUMBER_OF_ARGUMENTS = -1;

ActionBundle::ActionBundle()
{
	
}

void ActionBundle::setAction(Action action)
{
    bundle[UNDEFINED_NUMBER_OF_ARGUMENTS][""] = action;
}

void ActionBundle::setAction(vector<string>&& prototype, Action action)
{
    auto len = prototype.size();
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
    cout << len << " :: " << proto_str << endl;
    bundle[len][proto_str] = action;
}

ProtoMap& ActionBundle::getProtoMap(int nargs)
{
    return bundle[nargs];
}

bool ActionBundle::existsProtoMap(int nargs) const
{
    return bundle.find(nargs) != bundle.end();
}

int ActionBundle::getMax() const
{
    return bundle.empty() ? -2 : bundle.cbegin()->first;
}

int ActionBundle::getMin() const
{
    int mini = -2;
    for(auto it = bundle.begin(); it != bundle.end(); it++)
    {
        mini = it->first;
    }
    return mini;
}
