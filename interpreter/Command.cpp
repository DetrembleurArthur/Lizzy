#include "Command.hpp"


using namespace std;
using namespace lizzy;


Command::Command(const std::string &name, const Packageable *super) : Packageable(name, super), actionBundle(nullptr)
{

}

Command::~Command()
{
    if(actionBundle != nullptr)
    {
        delete actionBundle;
    }
}

ActionBundle& Command::getActionBundle()
{
    if(actionBundle == nullptr)
    {
        actionBundle = new ActionBundle();
    }
    return *actionBundle;
}
