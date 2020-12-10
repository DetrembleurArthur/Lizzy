#include "Package.hpp"

using namespace std;
using namespace lizzy;


Package *Package::create(const std::string& name)
{
    return new Package(name);
}

Package::Package(const string& name, const Packageable* super) : Packageable(name, super)
{
    Debug::loginfo("create package: " + getViewFullName());
}

Package::~Package()
{
    for(Packageable *child : children)
    {
        delete child;
    }
    Debug::loginfo("destroy package: " + getViewFullName());
}

void Package::removePackage(const std::string& name)
{
    if(existsPackage(name))
        remove(name);
    throw LZException(name + " package not exists on " + getViewFullName() + " package");
}

bool Package::existsPackage(const std::string& name)
{
    return dynamic_cast<Package * >(get(name));
}

Package *Package::getPackage(const std::string& name)
{
    return dynamic_cast<Package *>(get(name));
}

Package& Package::createPackage(const string& name)
{
    string pkgname;
    string subname;
    extractNames(name, pkgname, subname);
    
    if(subname.size())
    {
        for(int i = 0; i < children.size(); i++)
        {
            if(dynamic_cast<Package *>(children[i]))
            {
                if(children[i]->getName() == pkgname)
                {
                    return dynamic_cast<Package *>(children[i])->createPackage(subname);
                }
            }
        }
        Package *pkg = new Package(pkgname, this);
        children.push_back(pkg);
        return pkg->createPackage(subname);
    }
    else
    {
        if(existsPackage(name))
            throw LZException(name + " package already exists on " + getViewFullName() + " package");
        Package *pkg = new Package(name, this);
        children.push_back(pkg);
        return *pkg;
    }
}

void Package::remove(const string& name)
{
    string pkgname;
    string subname;
    extractNames(name, pkgname, subname);

    for(int i = 0; i < children.size(); i++)
    {
        if(children[i]->getName() == pkgname)
        {
            if(subname.size())
            {
                if(dynamic_cast<Package *>(children[i]))
                    dynamic_cast<Package *>(children[i])->removePackage(subname);
                else
                    dynamic_cast<Command *>(children[i])->removeSubCommand(subname);
            }
            else
            {
                delete children[i];
                children.erase(children.begin() + i);
            }
            break;  
        }
    }
    throw LZException(name + " element not exists on " + getViewFullName() + " package");
}

bool Package::exists(const std::string& name)
{
    return get(name);
}

Packageable *Package::get(const std::string& name)
{
    string pkgname;
    string subname;
    extractNames(name, pkgname, subname);
    for(int i = 0; i < children.size(); i++)
    {
        if(children[i]->getName() == pkgname)
        {
            if(subname.size())
            {
                if(dynamic_cast<Package *>(children[i]))
                    return dynamic_cast<Package *>(children[i])->get(subname);
                else
                    return dynamic_cast<Command *>(children[i])->getSubCommand(subname);
            }
            else
            {
                return children[i];
            }
            break;  
        }
    }
    return nullptr;
}

void Package::search(const std::string& name, std::vector<Command *>& occurences)
{
    Command *cmd = getCommand(name);
    if(not cmd)
    {
        for(int i = 0; i < children.size(); i++)
        {
            if(dynamic_cast<Package *>(children[i]))
            {
                dynamic_cast<Package *>(children[i])->search(name, occurences);
            }
        }
    }
    else
    {
        occurences.push_back(cmd);
    }
}


void Package::searchExceptionThrowing(const std::string& name, std::vector<Command *>& occurences)
{
    switch(occurences.size())
    {
        case 0:
            throw LZException("no '" + name + "' symbol found through " + getViewFullName() + " package");
        case 1:
            break;
        default:
            string buffer = "multiple occurence of " + name + " command through " + getViewFullName() + " package:\n";
            for(auto c : occurences)
            {
                buffer += "\t" + c->getViewFullName() + "\n";
            }
            throw LZException(buffer);
    }
}

Command& Package::createCommand(const std::string &name)
{
    string cmdname;
    string subname;
    extractNames(name, cmdname, subname);

    for(int i = 0; i < children.size(); i++)
    {
        if(dynamic_cast<Command *>(children[i]))
        {
            if(children[i]->getName() == cmdname)
            {
                if(subname.size())
                {
                    return dynamic_cast<Command *>(children[i])->createSubCommand(subname);
                }
                else
                {
                    throw LZException(name + " command already exists on " + getViewFullName() + " package");
                }
            }
        }
    }
    Command *command = new Command(cmdname, this);
    children.push_back(command);
    if(subname.size())
        return command->createSubCommand(subname);
    return *command;
}

void Package::removeCommand(const std::string& name)
{
    if(existsCommand(name))
        remove(name);
    throw LZException(name + " command not exists on " + getViewFullName() + " package");
}

bool Package::existsCommand(const std::string& name)
{
    return dynamic_cast<Command * >(get(name));
}

Command *Package::getCommand(const std::string& name)
{
    return dynamic_cast<Command *>(get(name));
}

std::string Package::getViewFullName() const
{
    return super ? super->getViewFullName() + ".\033[96m" + getName() + "\033[0m" : "\033[96m" + getName() + "\033[0m";
}
