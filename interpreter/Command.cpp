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
    for(Command *sub : subcommands)
    {
        delete sub;
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

Command& Command::createSubCommand(const std::string& name)
{
    string cmdname;
    string subname;
    extractNames(name, cmdname, subname);
    for(Command *cmd : subcommands)
    {
        if(cmdname == cmd->getName())
        {
            if(subname.size())
            {
                return cmd->createSubCommand(subname);
            }
            else
            {
                throw LZException(getFullName() + "." + name + " command already exists");
            }
        }
    }
    Command *cmd = new Command(cmdname, this);
    subcommands.push_back(cmd);
    if(subname.size())
    {
        return cmd->createSubCommand(subname);
    }
    return *cmd;
}

void Command::removeSubCommand(const std::string& name)
{
    string cmdname;
    string subname;
    extractNames(name, cmdname, subname);
    auto len = subcommands.size();
    for(int i = 0; i < len; i++)
    {
        if(cmdname == subcommands[i]->getName())
        {
            if(subname.size())
            {
                subcommands[i]->removeSubCommand(subname);
            }
            else
            {
                delete subcommands[i];
                subcommands.erase(subcommands.begin() + i);
            }
            return;
        }
    }
    throw LZException(name + " subcommand not exists on " + getFullName() + " command");
}

Command& Command::getSubCommand(const std::string& name)
{
    string cmdname;
    string subname;
    extractNames(name, cmdname, subname);
    for(Command *sub : subcommands)
    {
        if(sub->getName() == cmdname)
        {
            if(subname.size())
            {
                return sub->getSubCommand(subname);
            }
            else
            {
                return *sub;
            }
        }
    }
    throw LZException(name + " subcommand not exists on " + getFullName() + " command");
}
