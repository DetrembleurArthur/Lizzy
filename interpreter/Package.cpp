#include "Package.hpp"

using namespace std;
using namespace lizzy;


Package::Package(const string& name, const Packageable* super) : Packageable(name, super)
{
    
}

Package::~Package()
{
    for(Packageable *child : children)
    {
        delete child;
    }
}

void Package::extractPackageNames(const std::string& name, std::string& dstcurrent, std::string& dstsub)
{
    int i = name.find(".");
    if(i != string::npos)
    {
        if(i == name.size() - 1)
            throw LZException(name + " package path is not correctly formatted");
        dstsub = name.substr(i + 1);
        dstcurrent = name.substr(0, i);
    }
    else
    {
        dstsub = "";
        dstcurrent = name;
    }
}

Package& Package::addPackage(const string& name)
{
    string pkgname;
    string subname;
    extractPackageNames(name, pkgname, subname);

    if(subname.size())
    {
        for(int i = 0; i < children.size(); i++)
        {
            if(dynamic_cast<Package *>(children[i]))
            {
                if(children[i]->getName() == pkgname)
                {
                    return dynamic_cast<Package *>(children[i])->addPackage(subname);
                }
            }
        }
        Package *pkg = new Package(pkgname, this);
        children.push_back(pkg);
        pkg->addPackage(subname);
    }
    else
    {
        if(existsPackage(name))
            throw LZException(name + " package already exists");
        Package *pkg = new Package(name, this);
        children.push_back(pkg);
        return *pkg;
    }
}

void Package::removePackage(const string& name)
{
    string pkgname;
    string subname;
    extractPackageNames(name, pkgname, subname);

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
}

bool Package::existsPackage(const std::string& name)
{
    string pkgname;
    string subname;
    extractPackageNames(name, pkgname, subname);

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
    extractPackageNames(name, pkgname, subname);

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
    throw LZException(name + " package does not exists");
}
