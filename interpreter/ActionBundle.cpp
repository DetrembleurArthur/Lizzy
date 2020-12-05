#include "ActionBundle.hpp"


using namespace std;
using namespace lizzy;

const int ActionBundle::UNDEFINED_NUMBER_OF_ARGUMENTS = -1;

ActionBundle::ActionBundle()
{
	
}

void ActionBundle::setAction(Action action)
{
    hash<string> hashGen;
    bundle[UNDEFINED_NUMBER_OF_ARGUMENTS][hashGen("")] = action;
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
            proto_str += "&" + prototype[i];
        }
    }
    hash<string> hashGen;
    bundle[len][hashGen(proto_str)] = action;
    Debug::loginfo("define action: " + to_string(len) + " : " + proto_str + " : " + to_string(hashGen(proto_str)));
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
