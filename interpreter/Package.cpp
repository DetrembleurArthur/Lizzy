#include "Package.hpp"

using namespace std;
using namespace lizzy;


Package::Package(const std::string& name, const Extractable* super) : Extractable(name, super)
{

}

Package::~Package()
{
    for(Extractable *child : children)
    {
        delete child;
    }
}

Package& Package::addPkg(const std::string& pkgname)
{
    Package *pkg = new Package(pkgname, this);
    children.push_back(pkg);
    return *this;
}
