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
            proto_str += "&" + prototype[i];
        }
    }
    bundle[len][proto_str] = action;
    Debug::loginfo("define action: " + to_string(len) + " : " + proto_str);
}

ProtoMap& ActionBundle::getProtoMap(int nargs)
{
    if(bundle.find(nargs) != bundle.end())
        return bundle[nargs];
    return bundle[UNDEFINED_NUMBER_OF_ARGUMENTS];
}

bool ActionBundle::existsProtoMap(int nargs) const
{
    return bundle.find(nargs) != bundle.end() or bundle.find(UNDEFINED_NUMBER_OF_ARGUMENTS) != bundle.end();
}

int ActionBundle::getMax() const
{
    if(existsProtoMap(UNDEFINED_NUMBER_OF_ARGUMENTS))
        return UNDEFINED_NUMBER_OF_ARGUMENTS;
    if(bundle.empty())
        return -2;
    auto it = bundle.end();
    it--;
    return it->first;
}

int ActionBundle::getMin() const
{
    int mini = bundle.empty() ? -2 : bundle.begin()->first;
    return mini;
}
