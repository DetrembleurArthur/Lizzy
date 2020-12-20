#include "ActionBundle.hpp"


using namespace std;
using namespace lizzy;


void Prototype::set(std::vector<int (*)(LZDataType *)>& condition, Action action)
{
    conditions.push_back(condition);
    actions.push_back(action);
}

void Prototype::set(Action action)
{
    conditions.push_back({});
    actions.push_back(action);
}

void Prototype::setArgs(int n)
{
    nargs = n;
}

Action Prototype::get(std::vector<LZDataType *>& data)
{
    if(nargs == -1)
        return actions[0];
    int i, j;
    bool brk;
    int finalScore = -1;
    Action action = nullptr;
    for(i = 0; i < conditions.size(); i++)
    {
        auto len = conditions[i].size();
        int score = 0;
        for(j = 0, brk = false; j < len and not brk; j++)
        {
            switch(conditions[i][j](data[j]))
            {
                case -1: //casting
                    score += 1;
                    break;
                case 1: //match
                    score += 2;
                    break;
                case 0: //not match
                    brk = true;
                    break;
            }
            Debug::logwarn("MATCH: " + data[j]->getId());
        }
        if(not brk and finalScore < score)
        {
            finalScore = score;
            Debug::logfatal("SCORE: " + to_string(finalScore));
            action = actions[i];
        }
    }
    if(finalScore != -1)
    {
        return action;
    }
    string proto = "";
    for(auto *datat : data)
        proto += datat->getId() + ", ";
    if(proto.size())
        proto = proto.substr(0, proto.size()-2);
    throw LZException("prototype matching error: " + proto);
}

 /*--------------------------------------------------------------*/


const int ActionBundle::UNDEFINED_NUMBER_OF_ARGUMENTS = -1;

ActionBundle::ActionBundle()
{
	
}

void ActionBundle::setAction(Action action)
{
    if(bundle.find(UNDEFINED_NUMBER_OF_ARGUMENTS) == bundle.end())
        bundle[UNDEFINED_NUMBER_OF_ARGUMENTS] = Prototype();
    bundle[UNDEFINED_NUMBER_OF_ARGUMENTS].set(action);
}

void ActionBundle::setAction(std::vector<int (*)(LZDataType *)>&& condition, Action action)
{
    auto len = condition.size();
    if(bundle.find(len) == bundle.end())
        bundle[len] = Prototype();
    bundle[len].set(condition, action);
}

Prototype& ActionBundle::getPrototype(int nargs)
{
    if(bundle.find(nargs) != bundle.end())
        return bundle[nargs];
    return bundle[UNDEFINED_NUMBER_OF_ARGUMENTS];
}

bool ActionBundle::existsPrototype(int nargs) const
{
    return bundle.find(nargs) != bundle.end() or bundle.find(UNDEFINED_NUMBER_OF_ARGUMENTS) != bundle.end();
}

int ActionBundle::getMax() const
{
    if(existsPrototype(UNDEFINED_NUMBER_OF_ARGUMENTS))
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

