#include "Package.hpp"

using namespace std;
using namespace lizzy;


Package *Package::create(const std::string& name)
{
    return new Package(name);
}

Package::Package(const string& name, const Packageable* super) : Packageable(name, super)
{
    
}

Package::~Package()
{
    for(Packageable *child : children)
    {
        delete child;
    }
    cout << "clear package " << getViewFullName() << endl;
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
                else
                {
                    throw LZException(name + " package already exists on " + getViewFullName() + " package");
                }
            }
        }
        Package *pkg = new Package(pkgname, this);
        children.push_back(pkg);
        pkg->createPackage(subname);
        return *pkg;
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

void Package::removePackage(const string& name)
{
    string pkgname;
    string subname;
    extractNames(name, pkgname, subname);

    for(int i = 0; i < children.size(); i++)
    {
        if(dynamic_cast<Package *>(children[i]))
        {
            if(children[i]->getName() == pkgname)
            {
                if(subname.size())
                {
                    dynamic_cast<Package *>(children[i])->removePackage(subname);
                }
                else
                {
                    delete children[i];
                    children.erase(children.begin() + i);
                }
                break;  
            }
        }
    }
    throw LZException(name + " package not exists on " + getViewFullName() + " package");
}

bool Package::existsPackage(const std::string& name)
{
    string pkgname;
    string subname;
    extractNames(name, pkgname, subname);

    for(int i = 0; i < children.size(); i++)
    {
        if(dynamic_cast<Package *>(children[i]))
        {
            if(children[i]->getName() == pkgname)
            {
                if(subname.size())
                {
                    return dynamic_cast<Package *>(children[i])->existsPackage(subname);
                }
                else
                {
                    return true;
                }
                break;  
            }
        }
    }
    return false;
}

Package& Package::getPackage(const std::string& name)
{
    string pkgname;
    string subname;
    extractNames(name, pkgname, subname);

    for(int i = 0; i < children.size(); i++)
    {
        if(dynamic_cast<Package *>(children[i]))
        {
            if(children[i]->getName() == pkgname)
            {
                if(subname.size())
                {
                    return dynamic_cast<Package *>(children[i])->getPackage(subname);
                }
                else
                {
                    return *dynamic_cast<Package *>(children[i]);
                }
                break;  
            }
        }
    }
    throw LZException(name + " package does not exists on " + getViewFullName() + " package");
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
    }
    throw LZException(name + " command not exists on " + getViewFullName() + " package");
}

bool Package::existsCommand(const std::string& name)
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
                    return dynamic_cast<Command *>(children[i])->existsSubCommand(subname);
                }
                else
                {
                    return true;
                }
                break;  
            }
        }
    }
    return false;
}

Command& Package::getCommand(const std::string& name)
{
    string cmdname;
    string subname;
    extractNames(name, cmdname, subname);

    for(int i = 0; i < children.size(); i++)
    {
        if(dynamic_cast<Package *>(children[i]))
        {
            if(children[i]->getName() == cmdname)
            {
                if(subname.size())
                {
                    return dynamic_cast<Command *>(children[i])->getSubCommand(subname);
                }
                else
                {
                    return *dynamic_cast<Command *>(children[i]);
                }
                break;  
            }
        }
    }
    throw LZException(name + " command does not exists on " + getViewFullName() + " package");
}

std::string Package::getViewFullName() const
{
    return super ? super->getViewFullName() + ".\033[96m" + getName() + "\033[0m" : "\033[96m" + getName() + "\033[0m";
}
